#pragma once

#include <array>
#include <vector>

#include "AtmosHolder.h"
#include "../Constheader.h"
#include "Interfaces.h"

class SyncRandom;
class IMapMaster;
class AtmosGrid;
class TextPainter;

class Atmosphere : public IAtmosphere
{
public:
    Atmosphere(SyncRandom* random, IMapMaster* map, TextPainter* texts);
    virtual void Resize(size_t x, size_t y, size_t z) override;
    virtual void Process() override;
    virtual void ProcessMove() override;
private:
    AtmosGrid* grid_;
    void LoadDataToGrid();
    void UnloadDataFromGrid();

    qint64 load_grid_ns_;
    qint64 unload_grid_ns_;
    qint64 grid_processing_ns_;

    qint64 movement_processing_ns_;

    void ProcessTileMove(size_t x, size_t y, size_t z);

    void ShuffleX();
    void ShuffleY();
    void ShuffleDir();
    std::vector<size_t> x_shuffle_;
    std::vector<size_t> y_shuffle_;
    size_t z_size_;

    std::array<Dir, 4> dir_shuffle_;

    SyncRandom* random_;
    IMapMaster* map_;
    TextPainter* texts_;
};