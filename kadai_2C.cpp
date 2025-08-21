//
// Created by rikuo on 25/08/17.
//
#include <GLFW/glfw3.h>
#include <vector>
#include <cmath>
#include <chrono>
#include <thread>
#include <cstdlib>
#include <ctime>

constexpr float PI = 3.1415926535f;

// -------- Vec2 & helpers --------
struct Vec2 {
    float x{0}, y{0};
    Vec2() = default;
    Vec2(float X, float Y): x(X), y(Y) {}
    Vec2 operator+(const Vec2& o) const { return {x+o.x, y+o.y}; }
    Vec2 operator-(const Vec2& o) const { return {x-o.x, y-o.y}; }
    Vec2 operator*(float s)       const { return {x*s, y*s}; }
    Vec2& operator+=(const Vec2& o){ x+=o.x; y+=o.y; return *this; }
    Vec2& operator-=(const Vec2& o){ x-=o.x; y-=o.y; return *this; }
};
static inline float dot(const Vec2&a,const Vec2&b){ return a.x*b.x + a.y*b.y; }
static inline float norm(const Vec2&a){ return std::sqrt(dot(a,a)); }
static inline Vec2  normalize(const Vec2&a){ float n=norm(a); return (n>1e-6f)? a*(1.0f/n):Vec2{}; }

// ============================================================
// ① Agent：物理特性 + Boids（自前の加速度 a_ を保持）
// ============================================================
class Agent {
public:
    Agent(const Vec2& p0, const Vec2& v0, float radius, float viewRadius)
        : p_(p0), v_(v0), radius_(radius), viewRad_(viewRadius) {}

    Vec2 randomForce(float strength) {
        float ang = ((float)std::rand() / RAND_MAX) * 2.f * PI;
        return Vec2{ std::cos(ang), std::sin(ang) } * strength;
    }

    // マスダンパ系： M a + D v = F_boids + F_wall
    void drive(float dt, const std::vector<Agent>& all, float worldW, float worldH)
    {
        Vec2 u_s{0,0};
        Vec2 u_c{0,0};
        Vec2 u_a{0,0};
        Vec2 u_wall{0,0};

        // TODO Boidsを実装


        Vec2 u_ran = randomForce(30.f)* k_ran_;  // strength=30


        // --- 壁：やわらかバネで内側へ ---
        // TODO 壁からの反発を計算

        //要素の合成
        Vec2 F_boids = u_s + u_a + u_c + u_wall + u_ran;

        // TODO マスダンパ系から加速度の計算
        a_ =
        clipAce(a_, Amax_);

        // TODO 積分して速度計算
        v_ =
        clipVec(v_, Vmax_);
        // TODO 積分して位置計算
        p_ =

        // --- 画面内にクランプ（半径ぶん内側） ---
        if (p_.x < radius_)   p_.x = radius_;
        if (p_.x > worldW-radius_) p_.x = worldW - radius_;
        if (p_.y < radius_)   p_.y = radius_;
        if (p_.y > worldH-radius_) p_.y = worldH - radius_;
    }

    // 描画用の読み取り
    Vec2  pos()     const { return p_; }
    float radius()  const { return radius_; }

private:
    // 状態
    Vec2  p_{0,0};
    Vec2  v_{0,0};
    Vec2  a_{0,0};

    // 見た目・近傍
    float radius_{3.f};
    float viewRad_{200.f};

    // 物理パラメータ（マス・ダンパ）
    float M_ = 1.0f;   // 質量
    float D_ = 1.0f;   // 粘性係数（減衰）

    // Boids ゲイン
    // todo 必要ならゲインは変えてOK
    float k_sep_  = 4.f;
    float k_ali_  = 10.f;
    float k_coh_  = 2.f;
    float k_wall_ = 2.f;
    float k_ran_ = 10.f;

    // 制限
    float Vmax_ = 100.f;
    float Amax_ = 100.f;

    static void clipVec(Vec2& v, float vmax){
        float vn = norm(v);
        if (vn > vmax) v = v * (vmax / (vn + 1e-6f));
    }
    static void clipAce(Vec2& a, float amax){
        float n = norm(a);
        if (n > amax) a = a * (amax / (n + 1e-6f));
    }
};

// ============================================================
// ② Renderer：GLFW初期化、背景色、エージェント描画
// ============================================================
class Renderer {
public:
    struct Color3 { float r{1.f}, g{1.f}, b{1.f}; };

    Renderer(int W, int H, const char* title)
        : W_(W), H_(H)
    {
        if (!glfwInit()) ok_ = false;
        window_ = glfwCreateWindow(W_, H_, title, nullptr, nullptr);
        if (!window_) { glfwTerminate(); ok_ = false; return; }
        glfwMakeContextCurrent(window_);

        glMatrixMode(GL_PROJECTION); glLoadIdentity();
        glOrtho(0, W_, H_, 0, -1, 1);
        glMatrixMode(GL_MODELVIEW);

        setBackground(1.f, 1.f, 1.f);
    }

    ~Renderer(){ if (window_) glfwDestroyWindow(window_); glfwTerminate(); }

    bool good() const { return ok_; }
    bool shouldClose() const { return glfwWindowShouldClose(window_); }
    void setBackground(float r, float g, float b){ bg_ = {r,g,b}; }

    void beginFrame() const { glClearColor(bg_.r, bg_.g, bg_.b, 1.f); glClear(GL_COLOR_BUFFER_BIT); }

    void drawAgent(const Agent& a) const {
        const Vec2 p = a.pos();
        const float r = a.radius();
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(p.x, p.y);
        const int seg = 24;
        for (int i=0; i<=seg; ++i) {
            float ang = 2.f*PI*i/seg;
            glVertex2f(p.x + r*std::cos(ang), p.y + r*std::sin(ang));
        }
        glEnd();
    }
    void drawAgents(const std::vector<Agent>& agents) const {
        glColor3f(0.9f, 0.1f, 0.1f);
        for (const auto& a : agents) drawAgent(a);
    }
    void endFrame() const { glfwSwapBuffers(window_); glfwPollEvents(); }

private:
    int W_, H_;
    bool ok_{true};
    GLFWwindow* window_{nullptr};
    Color3 bg_{1.f,1.f,1.f};
};

// ============================================================
// ③ main：サンプリング・台数・領域・ループ
// ============================================================
int main(){
    const int   W   = 500;
    const int   H   = 500;
    const int   N   = 10;     // エージェント台数
    const float R   = 5.f;    // 半径
    const float VR  = 200.f;  // 視野半径
    const double dt = 0.01;   // サンプリング [s]（100Hz）

    std::srand((unsigned)std::time(nullptr));

    Renderer renderer(W, H, "Boids (mass-damper, a->v->p)");
    if (!renderer.good()) return -1;
    renderer.setBackground(1.f, 1.f, 1.f);

    std::vector<Agent> agents;
    agents.reserve(N);
    for (int i=0; i<N; ++i){
        float ang = (float)std::rand()/RAND_MAX * 2.f*PI;
        float spd = 40.f + (std::rand()%60);
        agents.emplace_back(
            Vec2{W*0.5f, H*0.5f},                      // 初期位置＝中心
            Vec2{std::cos(ang)*spd, std::sin(ang)*spd},// 初期速度
            R, VR
        );
    }

    auto next = std::chrono::steady_clock::now();
    while (!renderer.shouldClose()) {
        const std::vector<Agent> snap = agents;       // 同時刻参照

        for (auto& a : agents) {
            a.drive((float)dt, snap, (float)W, (float)H); // ★uは使わない
        }

        renderer.beginFrame();
        renderer.drawAgents(agents);
        renderer.endFrame();

        next += std::chrono::duration_cast<std::chrono::steady_clock::duration>(
                    std::chrono::duration<double>(dt));
        std::this_thread::sleep_until(next);
    }
    return 0;
}
