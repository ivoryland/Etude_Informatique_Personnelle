#pragma once
#ifndef UNICODE
    #define UNICODE
#endif

#ifndef NOMINMAX
    #define NOMINMAX
#endif

#include <Windows.h>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <tchar.h>
#include <string>

//Propre a visual studio
#pragma comment(lib, "user32.lib")

/**
Espace contenant toutes nos structures et classes nécessaires
pour développer l'espace de notre console virtuelle
**/
namespace gui{
    //On assure pour nos futures classes qui nécessite cettre classe qu'elle existe quelque part lors de la compilation
    class Console;

    const uint8_t nDefautAlpha = 0xFF;
    constexpr uint8_t nDefautPixel = (nDefautAlpha << 24);
    
    //°-------------------------------------------------------------°
    //|         rcode - nos valeurs de retour si c'est OK ou NON    |
    //°-------------------------------------------------------------°
    enum rcode {FAIL = 0, OK = 1, NO_FILE = -1};

    /**
    Représentation d'un vecteur 2D générique possédant
    une coordonnée x et y Et les opérations surdéfinies nécessaires

    Exemple d'implémentation de cette structure : 
            | typedef Vecteur2D<int> vi2D; |
            | typedef Vecteur2D<double> vd2D; |
            | typedef Vecteur2D<uint32_t> vu2D; |

    TEST : OK
    **/
    template <class T>
    struct Vecteur2D {
        T x = 0;
        T y = 0;
        Vecteur2D() : x(0), y(0) {}
        Vecteur2D(T _x, T _y) : x(_x), y(_y) {}
        Vecteur2D(const Vecteur2D& v) : x(v.x), y(v.y) {}
        Vecteur2D& operator= (const Vecteur2D& v) = default;
        Vecteur2D operator+ (const Vecteur2D& v) const { return Vecteur2D(x + v.x, y + v.y); }
        Vecteur2D operator- (const Vecteur2D& v) const { return Vecteur2D(x - v.x, y - v.y); }
        Vecteur2D operator* (const Vecteur2D& v) const { return Vecteur2D(x * v.x, y * v.y); }
        Vecteur2D operator* (const T& v) const { return Vecteur2D(x * v, y * v); }
        Vecteur2D operator/ (const Vecteur2D& v) const { return Vecteur2D(x / v.x, y / v.y); }
        Vecteur2D operator/ (const T& v) const { return Vecteur2D(x / v, y / v); }
        Vecteur2D& operator+= (const Vecteur2D& v) { this->x += v.x; this->y += v.y; return *this; }
        Vecteur2D& operator-= (const Vecteur2D& v) { this->x -= v.x; this->y -= v.y; return *this; }
        Vecteur2D& operator*= (const Vecteur2D& v) { this->x *= v.x; this->y *= v.y; return *this; }
        Vecteur2D& operator*= (const T& v) { this->x *= v; this->y *= v; return *this; }
        Vecteur2D& operator/= (const Vecteur2D& v) { this->x /= v.x; this->y /= v.y; return *this; }
        Vecteur2D& operator/= (const T& v) { this->x /= v; this->y /= v; return *this; }

        bool operator== (const Vecteur2D& v) const { return (this->x == v.x && this->y == v.y); }
        bool operator!= (const Vecteur2D& v) const { return (this->x != v.x && this->y != v.y); }

        const std::string str() const { return std::string("[ " + std::to_string(this->x) + " , " + std::to_string(this->y) + " ]"); }

        T norme2() const { return (x * x) + (y * y); }

        friend std::ostream& operator<< (std::ostream& o, const Vecteur2D& v) { return (o << v.str()); }
    };

    //°---------------------------------------------------------°
    //|         Définition de nos variables                     |
    //°---------------------------------------------------------°

    typedef Vecteur2D<int32_t> vi2D;
    typedef Vecteur2D<uint32_t> vu2D;
    typedef Vecteur2D<float> vf2D;
    typedef Vecteur2D<double> vd2D;

    vi2D vTailleEcran = { 240, 400 };
    vi2D vTaillePixel = { 4, 4 };
    vi2D vTailleFenetre = { 0,0 };
    bool bPleinEcran = false;
    vf2D vPixel = { 1.0f, 1.0f };

    struct Controleur {
        bool cPresse;
        bool cRelache;
        bool cMaintenu;
    };

    enum Touche {
        NONE,
        A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
        K0, K1, K2, K3, K4, K5, K6, K7, K8, K9,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        UP, DOWN, LEFT, RIGHT,
        SPACE, TAB, SHIFT, CTRL, INS, DEL, HOME, END, PGUP, PGDN,
        BACK, ESCAPE, RETURN, ENTER, PAUSE, SCROLL,
        NP0, NP1, NP2, NP3, NP4, NP5, NP6, NP7, NP8, NP9,
        NP_MUL, NP_DIV, NP_ADD, NP_SUB, NP_DECIMAL, PERIOD,
        EQUALS, COMMA, MINUS,
        OEM_1, OEM_2, OEM_3, OEM_4, OEM_5, OEM_6, OEM_7, OEM_8,
        CAPS_LOCK, ENUM_END
    };

    //°---------------------------------------------------------°
    //|         Pixel - INTEERFACE                              |
    //°---------------------------------------------------------°

    struct pixel {
        union {
            uint32_t n = nDefautPixel;
            struct { uint8_t r; uint8_t v; uint8_t b; uint8_t a; };
        };

        pixel();
        pixel(uint8_t rouge, uint8_t vert, uint8_t bleu, uint8_t alpha);
        pixel(uint32_t p);
        pixel& operator = (const pixel& p) = default;
        bool operator == (const pixel& p) const;
        bool operator != (const pixel& p) const;
        pixel operator * (const float f) const;
        pixel operator / (const float f) const;
        pixel& operator *= (const float f);
        pixel& operator /= (const float f);
        pixel operator + (const pixel& p) const;
        pixel operator - (const pixel p) const;
        pixel& operator += (const pixel& p);
        pixel& operator -= (const pixel p);
        pixel operator * (const pixel& p) const;
    };

    //°---------------------------------------------------------°
    //|         Pixel - FIN INTEERFACE                          |
    //°---------------------------------------------------------°
  
    //°---------------------------------------------------------°
    //|         Vitre - INTEERFACE                              |
    //°---------------------------------------------------------°
    /**
    C'est notre 
    **/
    class Vitre
    {
    public:
        virtual ~Vitre() = default;
        virtual rcode StartApplication() = 0;
        virtual rcode NettoyageApplication() = 0;
        virtual rcode StartThread() = 0;
        virtual rcode NettoyageThread() = 0;
        virtual rcode SetNomFenetre(const std::string& s) = 0;
        virtual rcode StartBoucleEvenementSysteme() = 0;
        virtual rcode CreationFenetreVitre(const vi2D& positionFenetre, const vi2D& tailleFenetre, bool pleinEcran) = 0;
        static Console* ptrConsole;
    };
    //°---------------------------------------------------------°
    //|         Vitre - FIN INTEERFACE                              |
    //°---------------------------------------------------------°

    //pour avoir un accés partout dans le code et qu'il soit unique
    static std::unique_ptr<Vitre> vitre;

    //°---------------------------------------------------------°
    //|         Console - INTEERFACE                            |
    //°---------------------------------------------------------°

    class Console {
    public:
        std::string sNomApplication;

        //------------------Constructeur-------------------
        Console();
        virtual ~Console();

        rcode Constructeur(int32_t fenetre_l, int32_t fenetre_h, int32_t pixel_l, int32_t pixel_w,
            const bool pleinEcran = false);
        rcode Start();

        //Implémentations coté utilisateur
        /*Appeler une fois lors de du démarage de l'application*/
        virtual bool initialisation();
        /*Appeler a chaque frame avec le temps deltaT en tre deux frame*/
        virtual bool mise_A_Jour(float deltaT);
        /*Appeler lorsque l'utilisateur quitte l'application*/
        virtual bool destruction();

        //Implémentation coté hardware
        /*Retourne vrai si la fenêtre est actuellemnt le focus*/
        bool estFocus()const;
        /*Retourn l'état d'une touche de clavier spécifique*/
        Controleur getKey(Touche t) const;
        /*Retourn l'état d'un bouton de souris spécifique*/
        Controleur getSouris(uint32_t b) const;
        /*Retourne la coordonnée x de la souris*/
        int32_t getMouseX() const;
        /*Retourne la coordonnée y de la souris*/
        int32_t getMouseY() const;
        /*Retourne la molette  de la souris*/
        int32_t getMouseMolette() const;

        /**
        Permet une souplesse pour de prochaine implémentation
        **/
        virtual void gui_ConfigurationSysteme();

        const vi2D& getFenetreSouris() const;
    };
    //°---------------------------------------------------------°
    //|         Console - FIN INTEERFACE                        |
    //°---------------------------------------------------------°

}

/*

*/
namespace gui {

    //°---------------------------------------------------------°
    //|         Pixel - IMPLEMENTATION                          |
    //°---------------------------------------------------------°
    pixel::pixel() { r = 0; v = 0; b = 0; a = nDefautAlpha; }
    inline pixel::pixel(uint8_t rouge, uint8_t vert, uint8_t bleu, uint8_t alpha) { n = rouge | (vert << 8) | (bleu << 16) | (alpha << 24); }
    inline pixel::pixel(uint32_t p) { n = p; }
    inline bool pixel::operator==(const pixel& p) const { return n == p.n; }
    inline bool pixel::operator!=(const pixel& p) const { return n != p.n; }
    inline pixel pixel::operator*(const float f) const {
        float fR = std::min(255.0f, std::max(0.0f, float(r) * f));
        float fV = std::min(255.0f, std::max(0.0f, float(v) * f));
        float fB = std::min(255.0f, std::max(0.0f, float(b) * f));
        return pixel(uint8_t(fR), uint8_t(fV), uint8_t(fB), a);
    }
    inline pixel pixel::operator/(const float f) const {
        float fR = std::min(255.0f, std::max(0.0f, float(r) / f));
        float fV = std::min(255.0f, std::max(0.0f, float(v) / f));
        float fB = std::min(255.0f, std::max(0.0f, float(b) / f));
        return pixel(uint8_t(fR), uint8_t(fV), uint8_t(fB), a);
    }
    inline pixel& pixel::operator*=(const float f) {
        this->r = std::min(255.0f, std::max(0.0f, float(r) * f));
        this->v = std::min(255.0f, std::max(0.0f, float(v) * f));
        this->b = std::min(255.0f, std::max(0.0f, float(b) * f));
        return *this;
    }
    inline pixel& pixel::operator/=(const float f) {
        this->r = std::min(255.0f, std::max(0.0f, float(r) / f));
        this->v = std::min(255.0f, std::max(0.0f, float(v) / f));
        this->b = std::min(255.0f, std::max(0.0f, float(b) / f));
        return *this;
    }
    inline pixel pixel::operator+(const pixel& p) const {
        uint8_t R = std::min(255, std::max(0, int(r) + int(p.r)));
        uint8_t V = std::min(255, std::max(0, int(v) + int(p.v)));
        uint8_t B = std::min(255, std::max(0, int(b) + int(p.b)));
        return pixel(R, V, B, a);
    }
    inline pixel pixel::operator-(const pixel p) const {
        uint8_t R = std::min(255, std::max(0, int(r) - int(p.r)));
        uint8_t V = std::min(255, std::max(0, int(v) - int(p.v)));
        uint8_t B = std::min(255, std::max(0, int(b) - int(p.b)));
        return pixel(R, V, B, a);
    }
    inline pixel& pixel::operator+=(const pixel& p) {
        this->r = std::min(255, std::max(0, int(r) + int(p.r)));
        this->v = std::min(255, std::max(0, int(v) + int(p.v)));
        this->b = std::min(255, std::max(0, int(b) + int(p.b)));
        return *this;
    }
    inline pixel& pixel::operator-=(const pixel p) {
        this->r = std::min(255, std::max(0, int(r) - int(p.r)));
        this->v = std::min(255, std::max(0, int(v) - int(p.v)));
        this->b = std::min(255, std::max(0, int(b) - int(p.b)));
        return *this;
    }
    inline pixel pixel::operator*(const pixel& p) const{
        uint8_t R = std::min(255, std::max(0, int(r) * int(p.r)));
        uint8_t V = std::min(255, std::max(0, int(v) * int(p.v)));
        uint8_t B = std::min(255, std::max(0, int(b) * int(p.b)));
        return pixel(R, V, B, a);
    }
    //°---------------------------------------------------------°
    //|         Pixel - FIN IMPLEMENTAION                       |
    //°---------------------------------------------------------°

    //°---------------------------------------------------------°
    //|         Consol - IMPLEMENTAION                          |
    //°---------------------------------------------------------°
    inline gui::Console::Console() { 
        sNomApplication = "Console par defaut !";
        gui_ConfigurationSysteme();
    }
    gui::Console::~Console(){}
    inline rcode Console::Constructeur(int32_t ecran_l, int32_t ecran_h, int32_t pixel_l, int32_t pixel_w, const bool pleinEcran) {
        vTailleEcran = { ecran_l, ecran_h };
        vTaillePixel = { pixel_l, pixel_w };
        vTailleFenetre = vTailleEcran * vTaillePixel;
        bPleinEcran = pleinEcran;
        //vPixel = 2.0f / vTailleEcran;
        //{ 2.0f / vTailleEcran.x,  2.0f / vTailleEcran.y };

        if (vTaillePixel.x <= 0 || vTaillePixel.y <= 0 || vTailleEcran.x <= 0 || vTailleEcran.y <= 0)
            return gui::FAIL;
        return gui::OK;
    }
    rcode Console::Start() {
        if (vitre->StartApplication() != gui::OK)
            return gui::FAIL;

        if (vitre->CreationFenetreVitre({ 40, 40 }, vTailleFenetre, bPleinEcran) != gui::OK)
            return gui::FAIL;

        //Thread TODO plus tard
        if (vitre->StartBoucleEvenementSysteme() != gui::OK)
            return gui::FAIL;

        if (vitre->NettoyageApplication() != gui::OK)
            return gui::FAIL;
        return gui::OK;
    }
    inline bool Console::initialisation()
    {
        return false;
    }
    inline bool Console::mise_A_Jour(float deltaT)
    {
        return false;
    }
    inline bool Console::destruction()
    {
        return true;
    }
    inline bool Console::estFocus() const
    {
        return false;
    }
    inline Controleur Console::getKey(Touche t) const
    {
        return Controleur();
    }
    inline Controleur Console::getSouris(uint32_t b) const
    {
        return Controleur();
    }
    inline int32_t Console::getMouseX() const
    {
        return int32_t();
    }
    inline int32_t Console::getMouseY() const
    {
        return int32_t();
    }
    inline int32_t Console::getMouseMolette() const
    {
        return int32_t();
    }
    inline const vi2D& Console::getFenetreSouris() const
    {
        // TODO: insérer une instruction return ici
    }

    class Vitre_Windows : public Vitre {
    private:
        HWND gui_hwnd = nullptr;
        std::wstring ConvertionS2W(const std::string& s) {
            int count = MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, NULL, 0);
            wchar_t* buffer = new wchar_t[count];
            MultiByteToWideChar(CP_UTF8, 0, s.c_str(), -1, buffer, count);

            std::wstring w(buffer);
            delete[] buffer;
            return w;
        }
    public:
        virtual rcode StartApplication() override { return rcode::OK; }
        virtual rcode NettoyageApplication() override { return rcode::OK; }
        virtual rcode StartThread() override { return rcode::OK; }
        //TODO:
        virtual rcode NettoyageThread() override { return rcode::OK; }
        virtual rcode SetNomFenetre(const std::string& s) override {
            if (SetWindowText(gui_hwnd, ConvertionS2W(s).c_str()) != 0)
                return gui::FAIL;
            return gui::OK;
        }
        virtual rcode StartBoucleEvenementSysteme() override {
            MSG Msg;
            // Boucle de messages
            while (GetMessage(&Msg, NULL, 0, 0) > 0) {
                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
            }
            return gui::OK;
        }
        virtual rcode CreationFenetreVitre(const vi2D& positionFenetre, const vi2D& tailleFenetre, bool pleinEcran) override {
            WNDCLASSEX wcex;

            const wchar_t CLASS_NAME[] = L"Console_Infographie";

            wcex.cbSize = sizeof(WNDCLASSEX);
            wcex.style = CS_HREDRAW | CS_VREDRAW;
            wcex.lpfnWndProc = WndProc;
            wcex.cbClsExtra = 0;
            wcex.cbWndExtra = 0;
            wcex.hInstance = GetModuleHandle(nullptr);
            wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
            wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
            wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
            wcex.lpszMenuName = NULL;
            wcex.lpszClassName = CLASS_NAME;
            wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

            if (!RegisterClassEx(&wcex)) {
                MessageBox(NULL,
                    _T("Appel à RegisterClassEx failed"),
                    _T("Windoww Console Infographie"),
                    NULL);
                return gui::FAIL;
            }
            DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
            DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;

            vi2D vHautGauche = positionFenetre;

            if (pleinEcran) {
                dwExStyle = 0;
                HMONITOR hmon = MonitorFromWindow(gui_hwnd, MONITOR_DEFAULTTONEAREST);
                MONITORINFO mi = { sizeof(mi) };
                if (!GetMonitorInfo(hmon, &mi)) return rcode::FAIL;
                vTailleFenetre = { mi.rcMonitor.right, mi.rcMonitor.bottom };
                vHautGauche.x = 0;
                vHautGauche.y = 0;
            }


            RECT rWndRect = { 0, 0, tailleFenetre.x, tailleFenetre.y };
            AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);
            int width = rWndRect.right - rWndRect.left;
            int height = rWndRect.bottom - rWndRect.top - 90;

            gui_hwnd = CreateWindowEx(dwExStyle,          // Optional window styles.
                CLASS_NAME,                     // Window class
                L"Console pour interface graphique",    // Window text
                WS_OVERLAPPEDWINDOW,            // Window style

                // Size and position
                vHautGauche.x, vHautGauche.y, width, height,

                NULL,       // Parent window    
                NULL,       // Menu
                GetModuleHandle(nullptr),  // Instance handle
                NULL        // Additional application data
            );

            if (!gui_hwnd) {
                MessageBox(NULL,
                    _T("Call to CreateWindowEx failed!"),
                    _T("Windows Desktop Guided Tour"),
                    NULL);

                return gui::FAIL;
            }

            ShowWindow(gui_hwnd, 1);
            UpdateWindow(gui_hwnd);
            return gui::OK;
        }


        static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
            PAINTSTRUCT ps;
            HDC hdc;
            TCHAR greeting[] = _T("Ma premiere fenetre window Pour pouvoir dessiner dessus et faire tout plein de pixel");
            switch (msg) {
            case WM_PAINT: 
                hdc = BeginPaint(hwnd, &ps);

                // Here your application is laid out.
                // For this introduction, we just print out "Hello, Windows desktop!"
                // in the top left corner.
                TextOut(hdc,
                    5, 5,
                    greeting, _tcslen(greeting));
                // End application-specific layout section.

                EndPaint(hwnd, &ps);
                break;
            
            case WM_CLOSE:
                DestroyWindow(hwnd);
                break;
            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            }
            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

    };
}

namespace gui {
    class Vitre_Headless : public Vitre {
        virtual rcode StartApplication() { return gui::OK; }
        virtual rcode NettoyageApplication() { return gui::OK; }
        virtual rcode StartThread() { return gui::OK; }
        virtual rcode NettoyageThread() { return gui::OK; }
        virtual rcode SetNomFenetre(const std::string& s) { return gui::OK; }
        virtual rcode StartBoucleEvenementSysteme() { return gui::OK; }
        virtual rcode CreationFenetreVitre(const vi2D& positionFenetre, const vi2D& tailleFenetre, bool pleinEcran) { return gui::OK; }

    };
}


namespace gui {
    inline void gui::Console::gui_ConfigurationSysteme() {
        vitre = std::make_unique<Vitre_Windows>();
    }
}
