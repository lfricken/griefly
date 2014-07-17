#pragma once

#include "CAliveMob.h"

#include "sound.h"

class Item;

class COrk : public CAliveMob
{
public:
    DECLARE_GET_TYPE_ITEM(ork)
    DECLARE_SAVED(COrk, CAliveMob)
    COrk();
    virtual void aaMind();
    virtual void processGUI() override;//draw
    virtual void processGUImsg(const Message& msg) override;
    virtual void live() override;
    virtual bool checkMove(Dir direct) override;
    id_ptr_on<Item> KV_SAVEBLE(in_hand);
    int KV_SAVEBLE(jump_time);
private:
    GLSprite* KV_ON_LOAD(gui_sprite_, nullptr);
};

ADD_TO_TYPELIST(COrk);
