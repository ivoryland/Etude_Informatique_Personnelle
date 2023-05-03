#pragma once
#define NOMINMAX

#include <Windows.h>
#include <cstdint>
#include <algorithm>
#include <iostream>


#include "../Outils/Outils_math/Vecteur2D.h"

namespace gui{
    class Consol;
    const uint8_t nDefautAlpha = 0xFF;
    constexpr uint8_t nDefautPixel = (nDefautAlpha << 24);
    enum rcode {FAIL = 0, OK = 1, NO_FILE = -1};

    std::string sNomApplication;
    Vecteur2D vTailleEcran = { 240, 400 };
    Vecteur2D vTaillePixel = { 4, 4 };
    Vecteur2D vTailleFenetre = { 0,0 };
    bool bPleinEcran = false;
    Vecteur2D vPixel = { 1.0f, 1.0f };

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

    class Consol {
    public:
        //------------------Constructeur-------------------
        Consol();
        virtual ~Consol();

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

        const Vecteur2D& getFenetreSouris() const;
    };
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
    //|         Consol - FIN IMPLEMENTAION                       |
    //°---------------------------------------------------------°
    inline gui::Consol::Consol() { sNomApplication = "Consol defaut !"; }
    gui::Consol::~Consol(){}
    inline rcode Consol::Constructeur(int32_t fenetre_l, int32_t fenetre_h, int32_t pixel_l, int32_t pixel_w, const bool pleinEcran) {
        vTailleEcran = { fenetre_l, fenetre_h };
        vTaillePixel = { pixel_l, pixel_w };
        vTailleFenetre = { vTailleEcran.x * vTaillePixel.x, vTailleEcran.y * vTaillePixel.y };
        bPleinEcran = pleinEcran;
        vPixel = { 2.0f / vTailleEcran.x,  2.0f / vTailleEcran.y };

        if (vTaillePixel.x <= 0 || vTaillePixel.y <= 0 || vTailleEcran.x <= 0 || vTailleEcran.y <= 0)
            return gui::FAIL;
        return gui::OK;
    }
    inline rcode Consol::Start() {
        return rcode();
    }
    inline bool Consol::initialisation()
    {
        return false;
    }
    inline bool Consol::mise_A_Jour(float deltaT)
    {
        return false;
    }
    inline bool Consol::destruction()
    {
        return false;
    }
    inline bool Consol::estFocus() const
    {
        return false;
    }
    inline Controleur Consol::getKey(Touche t) const
    {
        return Controleur();
    }
    inline Controleur Consol::getSouris(uint32_t b) const
    {
        return Controleur();
    }
    inline int32_t Consol::getMouseX() const
    {
        return int32_t();
    }
    inline int32_t Consol::getMouseY() const
    {
        return int32_t();
    }
    inline int32_t Consol::getMouseMolette() const
    {
        return int32_t();
    }
    inline const Vecteur2D& Consol::getFenetreSouris() const
    {
        // TODO: insérer une instruction return ici
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    // Classe de la fenêtre
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = L"MaClasse";
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, L"Échec de l'enregistrement de la classe de fenêtre", L"Erreur", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Créer la fenêtre
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,   //Window styles
        L"MaClasse",        //Window class
        L"Ma fenêtre",      //Window text
        WS_OVERLAPPEDWINDOW,//Window style
        CW_USEDEFAULT, CW_USEDEFAULT, 640, 480,
        NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, L"Échec de la création de la fenêtre", L"Erreur", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Boucle de messages
    while (GetMessage(&Msg, NULL, 0, 0) > 0) {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_CLOSE:
        DestroyWindow(hwnd);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}
