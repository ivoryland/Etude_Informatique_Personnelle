#pragma once
namespace gui {
    //TODO : fichier d'initialisation et paramétrique
    const uint8_t nDefautAlpha = 0xFF;
    constexpr uint32_t nDefautPixel = (nDefautAlpha << 24);

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

    struct Controleur {
        bool cPresse;
        bool cRelache;
        bool cMaintenu;
    };

    //°---------------------------------------------------------°
    //|         Structure Pixel - INTEERFACE                    |
    //°---------------------------------------------------------°
   /**
   Représentation d'un pixel générique possédant
   son spectre de couleur rvb (rouge, vert, bleu)
   son gradiant alpha
   et enfin n, le rendu complet du pixel
   TEST : OK
   **/
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

        const std::string str() const;

        friend std::ostream& operator<< (std::ostream& o, const pixel& p) { return (o << p.str()); }

    };

    //°---------------------------------------------------------°
    //|        Structur Pixel - FIN INTEERFACE                  |
    //°---------------------------------------------------------°


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
        this->r = uint8_t(std::min(255.0f, std::max(0.0f, float(r) * f)));
        this->v = uint8_t(std::min(255.0f, std::max(0.0f, float(v) * f)));
        this->b = uint8_t(std::min(255.0f, std::max(0.0f, float(b) * f)));
        return *this;
    }
    inline pixel& pixel::operator/=(const float f) {
        this->r = uint8_t(std::min(255.0f, std::max(0.0f, float(r) / f)));
        this->v = uint8_t(std::min(255.0f, std::max(0.0f, float(v) / f)));
        this->b = uint8_t(std::min(255.0f, std::max(0.0f, float(b) / f)));
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
    inline pixel pixel::operator*(const pixel& p) const {
        uint8_t R = std::min(255, std::max(0, int(r) * int(p.r)));
        uint8_t V = std::min(255, std::max(0, int(v) * int(p.v)));
        uint8_t B = std::min(255, std::max(0, int(b) * int(p.b)));
        return pixel(R, V, B, a);
    }

    inline const std::string gui::pixel::str() const {
        return std::string("[ " + std::to_string(n) + " | "
        + std::to_string(r) + ", " + std::to_string(v) + ", " + std::to_string(b) + ", " + std::to_string(a) +" ]");
    }
    //°---------------------------------------------------------°
    //|         Pixel - FIN IMPLEMENTAION                       |
    //°---------------------------------------------------------°

}