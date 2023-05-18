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

//Fichiers essantiels pour l'application
#include "Configuration.h"
#include "StructuresRenduVisuel.h"
#include "IterateurImages.h"

//Propre à visual studio
#pragma comment(lib, "user32.lib")

//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//°---------------------------------------------------------°
//|         DEBUT INTEERFACE                                |
//°---------------------------------------------------------°
/**
Espace contenant toutes nos structures et classes nécessaires
pour développer l'espace de notre console virtuelle
**/
namespace gui{
    //On assure pour nos futures classes qui utilisent cette classe, existe quelque lors de la compilation
    class Console;

    //°-------------------------------------------------------------°
    //|         rcode - nos valeurs de retour si c'est OK ou NON    |
    //|         Toutes fonctions qui doit retourner l'état          |
    //|         de notre console utilisent cette enum               |
    //°-------------------------------------------------------------°
    enum class rcode {FAIL = 0, OK = 1, NO_FILE = -1};

    //°---------------------------------------------------------°
    //|         Définition de nos variables                     |
    //°---------------------------------------------------------°

    typedef Vecteur2D<int32_t> vi2D;
    typedef Vecteur2D<uint32_t> vu2D;
    typedef Vecteur2D<float> vf2D;
    typedef Vecteur2D<double> vd2D;

    vi2D vTailleEcran = { gui_conf::W_HAUTEUR, gui_conf::W_LARGEUR };
    vi2D vTaillePixel = { gui_conf::W_PIXEL_H, gui_conf::W_PIXEL_L};
    vi2D vTailleFenetre = { 0,0 };
    bool bPleinEcran = gui_conf::PLEINECRAN;
    vf2D vPixel = { 1.0f, 1.0f };

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
    //|         Ecran - INTEERFACE                              |
    //°---------------------------------------------------------°
    /**
    C'est notre écran
    **/
    class Ecran
    {
    public:
        virtual ~Ecran() = default;
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
    //|         Ecran - FIN INTEERFACE                          |
    //°---------------------------------------------------------°

    //pour avoir un accés partout dans le code et qu'il soit unique
    static std::unique_ptr<Ecran> ecran;

    //°---------------------------------------------------------°
    //|         graphisme_Bitmap - INTEERFACE                   |
    //°---------------------------------------------------------°
    /**
    graphisme_Bitmap est notre image a chaque frame, on peut le comparer a un sprite d'image
    Cette class s'occupe de contenir la mémoire pour l'instant présent.
    (Fun fact, sprite veut dire lutin, ... voila c'est tout ^^')
    **/
    template<class T>
    class graphisme_Bitmap {
    public:
        //Les pixels affichés à l'écran
        T** matricePixel;
        //Notre itérateur pour se déplacer dans la matrice 2D
        gui_ite::ImageTableau<T> ite_Tableau;

        //---------------------------------Contruscteur----------------------------
        graphisme_Bitmap(const T PixelDefaut, const int hauteur, const int largeur);
        ~graphisme_Bitmap() { delete[] matricePixel[0]; delete[] matricePixel; }

        /*
        * Méthode qui change le pixel désigné par les coordonnées x, y par p
        * Attention: il faut que p soit du même type que la classe
        */
        const bool setPixel(const int x, const int y, const T& p);
        /*
        * Méthode qui retourne le pixel désigné par les coordonnées x, y
        * Attention: il faut que p soit du même type que la classe
        */
        const T* getPixel(const int x, const int y)const;

        /*
        * Surdéfinition de string(), décrit la classe graphisme_Bitmap
        * @return string
        */
        operator std::string()const;

        /*
        * ostream << graphisme_Bitmap
        */
        friend std::ostream& operator<< (std::ostream& o, const graphisme_Bitmap& gb) { return (o << (std::string)gb); }
    };
    //°---------------------------------------------------------°
    //|         FIN graphisme_Bitmap - INTEERFACE               |
    //°---------------------------------------------------------°

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

        /*Retourne la hauteur de la fenetre sous forme de constante (Utile pour l'initialisation d'une fenetre)*/
        const int32_t hauteurFenetre()const;
        /*Retourne la largeur de la fenetre sous forme de constante (Utile pour l'initialisation d'une fenetre)*/
        const int32_t largeurFenetre()const;

        uint32_t getFPS()const;
        

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
//°---------------------------------------------------------°
//|         FIN INTEERFACE                                  |
//°---------------------------------------------------------°
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//°---------------------------------------------------------°
//|         DEBUT IMPLEMENTATION                            |
//°---------------------------------------------------------°

namespace gui {

    //°---------------------------------------------------------°
    //|         graphisme_Bitmap - IMPLEMENTAION                |
    //°---------------------------------------------------------°

    template<class T>
    inline graphisme_Bitmap<T>::graphisme_Bitmap(const T PixelDefaut, const int hauteur, const int largeur)
    {
        matricePixel = new T * [hauteur];
        T* dataContigu = new T[hauteur * largeur];
        int i, j;
        for (i = 0; i < largeur; i++) {
            matricePixel[i] = &dataContigu[i * largeur];
            for (j = 0; j < largeur; j++) {
                matricePixel[i][j] = i + j;
            }
        }

        ite_Tableau = gui_ite::ImageTableau<T>((T*)*matricePixel, hauteur - 1, largeur - 1, largeur);
    }

    template<class T>
    inline const bool graphisme_Bitmap<T>::setPixel(const int x, const int y, const T& p)
    {
        if (x >= 0 && y >= 0 && x < vTailleEcran.x && y < vTailleEcran.y) {
            ite_Tableau.setPixel(x, y, p);
            return true;
        }
        return false;
    }

    template<class T>
    inline const T* graphisme_Bitmap<T>::getPixel(const int x, const int y) const
    {
        if (x >= 0 && y >= 0 && x < vTailleEcran.x && y < vTailleEcran.y) {
            return ite_Tableau.getPixel(x, y);
        }
        return new T();
    }

    template<class T>
    inline graphisme_Bitmap<T>::operator std::string() const
    {
        std::string str = "";
        int i, j;
        for (i = 0; i < vTailleEcran.x; i++) {
            for (j = 0; j < vTailleEcran.y; j++) {
                str += std::to_string(*ite_Tableau.getPixel(i, j));
            }
            str += '\n';
        }
        return str;
    }

    //°---------------------------------------------------------°
    //|        FIN graphisme_Bitmap - IMPLEMENTAION             |
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
            return rcode::FAIL;
        return rcode::OK;
    }
    rcode Console::Start() {
        if (ecran->StartApplication() != rcode::OK)
            return rcode::FAIL;

        if (ecran->CreationFenetreVitre({ 40, 40 }, vTailleFenetre, bPleinEcran) != rcode::OK)
            return rcode::FAIL;

        //Thread TODO plus tard
        if (ecran->StartBoucleEvenementSysteme() != rcode::OK)
            return rcode::FAIL;

        if (ecran->NettoyageApplication() != rcode::OK)
            return rcode::FAIL;
        return rcode::OK;
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
    inline const int32_t Console::hauteurFenetre() const {
        if (vTailleFenetre.x <= 0)
            return gui_conf::W_HAUTEUR;
        return vTailleFenetre.x;
    }
    inline const int32_t Console::largeurFenetre() const {
        if (vTailleFenetre.y <= 0)
            return gui_conf::W_LARGEUR;
        return vTailleFenetre.y;
    }
    inline uint32_t Console::getFPS() const
    {
        return uint32_t();
    }
    inline const vi2D& Console::getFenetreSouris() const
    {
        // TODO: insérer une instruction return ici
    }

    //°---------------------------------------------------------°
    //|         FIN Consol - IMPLEMENTAION                      |
    //°---------------------------------------------------------°


    //°---------------------------------------------------------°
    //|         Ecran_Windows - IMPLEMENTAION ECRAN             |
    //°---------------------------------------------------------°

    class Ecran_Windows : public Ecran {
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

        //TODO: Implémenter le rendu visuel dans un thread
        virtual rcode StartThread() override { return rcode::OK; }
        virtual rcode NettoyageThread() override { return rcode::OK; }
        virtual rcode SetNomFenetre(const std::string& s) override {
            if (SetWindowText(gui_hwnd, ConvertionS2W(s).c_str()) != 0)
                return rcode::FAIL;
            return rcode::OK;
        }
        virtual rcode StartBoucleEvenementSysteme() override {
            MSG Msg;
            // Boucle de messages
            while (GetMessage(&Msg, NULL, 0, 0) > 0) {
                TranslateMessage(&Msg);
                DispatchMessage(&Msg);
            }
            return rcode::OK;
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
                return rcode::FAIL;
            }
            DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
            DWORD dwStyle = WS_CAPTION | WS_SYSMENU | WS_VISIBLE | WS_THICKFRAME;

            vi2D vHautGauche = positionFenetre;

            if (pleinEcran) {
                dwExStyle = 0;
                HMONITOR hmon = MonitorFromWindow(gui_hwnd, MONITOR_DEFAULTTONEAREST);
                MONITORINFO mi = { sizeof(mi) };
                if (!GetMonitorInfo(hmon, &mi)) return rcode::FAIL;
                vTailleFenetre = { mi.rcMonitor.bottom, mi.rcMonitor.right };
                vHautGauche.x = 0;
                vHautGauche.y = 0;
            }

            RECT rWndRect = { 0, 0, tailleFenetre.x, tailleFenetre.y };
            AdjustWindowRectEx(&rWndRect, dwStyle, FALSE, dwExStyle);
            int width = rWndRect.bottom - rWndRect.top - 30;
            int height = rWndRect.right - rWndRect.left - 72;

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

                return rcode::FAIL;
            }

            ShowWindow(gui_hwnd, 1);
            UpdateWindow(gui_hwnd);
            return rcode::OK;
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
               /* TextOut(hdc,
                    5, 5,
                    greeting, _tcslen(greeting));
                // End application-specific layout section.
                */
                SetPixel(hdc, 50, 50, RGB(255, 0, 0));
                SetPixel(hdc, 51, 50, RGB(255, 0, 0));
                SetPixel(hdc, 51, 51, RGB(255, 0, 0));
                SetPixel(hdc, 50, 51, RGB(255, 0, 0));
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

    //°---------------------------------------------------------°
    //|         FIN Ecran_Windows - IMPLEMENTAION               |
    //°---------------------------------------------------------°
}
//°---------------------------------------------------------°
//|         FIN IMPLEMENTAION                               |
//°---------------------------------------------------------°
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//°---------------------------------------------------------°
//|         DEBUT HEADLESS                                  |
//°---------------------------------------------------------°

namespace gui {
    /**
    Ecran_Headless est un classe fantôme
    c'est à dire qu'elle permet d'eviter de redéfinir toutes les méthodes contenues dans "Ecran"
    Très pratique, mais peut créer beaucoup de problème si on manque de rigueur
    **/
    class Ecran_Headless : public Ecran {
        virtual rcode StartApplication() { return rcode::OK; }
        virtual rcode NettoyageApplication() { return rcode::OK; }
        virtual rcode StartThread() { return rcode::OK; }
        virtual rcode NettoyageThread() { return rcode::OK; }
        virtual rcode SetNomFenetre(const std::string& s) { return rcode::OK; }
        virtual rcode StartBoucleEvenementSysteme() { return rcode::OK; }
        virtual rcode CreationFenetreVitre(const vi2D& positionFenetre, const vi2D& tailleFenetre, bool pleinEcran) { return rcode::OK; }
    };
}
//°---------------------------------------------------------°
//|         FIN HEADLESS                                    |
//°---------------------------------------------------------°
//_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-_-
//°---------------------------------------------------------°
//|         DEBUT CONFIGURATION OS                          |
//°---------------------------------------------------------°

namespace gui {
    /**
    Ici, on déclare a la toute fin la configurationSysteme de l'exploitant (: l'os du client)
    très pratique si on veut dévolpper cette application pour OS apple ou linux
    **/
    inline void gui::Console::gui_ConfigurationSysteme() {
        ecran = std::make_unique<Ecran_Windows>();
    }
}
//°---------------------------------------------------------°
//|         FIN CONFIGURATION OS                            |
//°---------------------------------------------------------°
