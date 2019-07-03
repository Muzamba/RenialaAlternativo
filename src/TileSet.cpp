#include "TileSet.h"



TileSet::TileSet(int tileWidth, int tileHeight, const std::string& file) : xablau (), tileSet(xablau, file), tileWidth(tileWidth), tileHeight(tileHeight) {
    if(tileSet.IsOpen()) {
        rows = std::round(tileSet.GetHeight() / tileHeight);
        columns = std::round(tileSet.GetWidth() / tileWidth);
    } else {
        std::cout << "Erro ao abrir o tileset: " << file << std::endl;
    }
}

void TileSet::RenderTile(unsigned index, float x, float y) {
    if(index <= (uint)(rows * columns - 1)) {
        int linha = std::round(index / columns);
        int coluna = std::round(index % columns);

        tileSet.SetClip(coluna * tileWidth, linha * tileHeight, tileWidth, tileHeight);
        tileSet.SetScale(1, 1);

        tileSet.Render(x, y);
    }
}

int TileSet::GetTileHeight() {
    return tileHeight;
}

int TileSet::GetTileWidth() {
    return tileWidth;
}
