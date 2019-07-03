#ifndef TRAB5_7_TEXT_H
#define TRAB5_7_TEXT_H

#include "Component.h"
#define INCLUDE_SDL_TTF
#include "SDL_include.h"
#include <memory>


class Text : public Component {
public:
    enum TextStyle {SOLID, SHADED, BLENDED};

    Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color);
    ~Text();

    void Update(float dt) override;
    void Render() override;
    bool Is(std::string type) override;

    void SetText(std::string text);
    void SetColor(SDL_Color color);
    void SetStyle(TextStyle style);
    void SetFile(std::string fontFile);
    void SetFontSize(int fontSize);

private:
    void RemakeTexture();


    std::shared_ptr<TTF_Font> font;
    std::string fontFile;
    int fontSize;
    TextStyle style;
    std::string text;
    SDL_Color color;
    SDL_Texture* texture;

};


#endif //TEXT_H
