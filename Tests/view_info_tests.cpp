#include "representation/ViewInfo.h"

#include <gtest/gtest.h>

TEST(FramesetInfoTest, SettersAndGetters)
{
    ViewInfo::FramesetInfo frameset_info;
    ASSERT_EQ(frameset_info.GetSprite(), "");
    ASSERT_EQ(frameset_info.GetState(), "");
    ASSERT_EQ(frameset_info.GetAngle(), 0);

    frameset_info.SetSprite("something");
    ASSERT_EQ(frameset_info.GetSprite(), "something");
    ASSERT_EQ(frameset_info.GetState(), "");
    ASSERT_EQ(frameset_info.GetAngle(), 0);

    frameset_info.SetState("11112");
    ASSERT_EQ(frameset_info.GetSprite(), "something");
    ASSERT_EQ(frameset_info.GetState(), "11112");
    ASSERT_EQ(frameset_info.GetAngle(), 0);

    frameset_info.SetAngle(42);
    ASSERT_EQ(frameset_info.GetSprite(), "something");
    ASSERT_EQ(frameset_info.GetState(), "11112");
    ASSERT_EQ(frameset_info.GetAngle(), 42);
}

TEST(FramesetInfoTest, IsSameSprites)
{
    ViewInfo::FramesetInfo frameset_info1;
    ASSERT_TRUE(ViewInfo::FramesetInfo::IsSameSprites(frameset_info1, frameset_info1));

    frameset_info1.SetSprite("sprite");
    frameset_info1.SetState("state");
    frameset_info1.SetAngle(42);
    ASSERT_TRUE(ViewInfo::FramesetInfo::IsSameSprites(frameset_info1, frameset_info1));

    ViewInfo::FramesetInfo frameset_info2;
    ASSERT_FALSE(ViewInfo::FramesetInfo::IsSameSprites(frameset_info1, frameset_info2));

    frameset_info2.SetSprite("sprite");
    frameset_info2.SetState("state");
    frameset_info2.SetAngle(42);
    ASSERT_TRUE(ViewInfo::FramesetInfo::IsSameSprites(frameset_info1, frameset_info2));    

    frameset_info2.SetSprite("sprite2");
    ASSERT_FALSE(ViewInfo::FramesetInfo::IsSameSprites(frameset_info1, frameset_info2));

    frameset_info2.SetSprite("sprite");
    frameset_info2.SetState("state2");
    ASSERT_FALSE(ViewInfo::FramesetInfo::IsSameSprites(frameset_info1, frameset_info2));

    frameset_info2.SetState("state");
    frameset_info2.SetAngle(43);
    ASSERT_FALSE(ViewInfo::FramesetInfo::IsSameSprites(frameset_info1, frameset_info2));
}

TEST(FramesetInfoTest, StreamOperators)
{
    ViewInfo::FramesetInfo frameset_info;
    frameset_info.SetSprite("sprite 1");
    frameset_info.SetState("state 2");
    frameset_info.SetAngle(84);

    std::stringstream str;
    str << frameset_info;

    ASSERT_EQ(str.str(), "8 sprite 1 7 state 2 84 ");

    str.str("8 sprite 2 7 state 3 -14");

    ViewInfo::FramesetInfo frameset_info2;
    str >> frameset_info2;
    ASSERT_EQ(frameset_info2.GetSprite(), "sprite 2");
    ASSERT_EQ(frameset_info2.GetState(), "state 3");
    ASSERT_EQ(frameset_info2.GetAngle(), -14);

    std::stringstream str2;
    str2 << frameset_info;
    ViewInfo::FramesetInfo frameset_info3;
    str2 >> frameset_info3;
    ASSERT_TRUE(ViewInfo::FramesetInfo::IsSameSprites(frameset_info, frameset_info3));
}

TEST(ViewInfoTest, AngleAndBaseFrameset)
{
    ViewInfo view_info;
    ASSERT_EQ(view_info.GetAngle(), 0);

    view_info.SetSprite("windows better than linux");
    ASSERT_EQ(view_info.GetBaseFrameset().GetSprite(), "windows better than linux");
    ASSERT_EQ(view_info.GetBaseFrameset().GetState(), "");
    ASSERT_EQ(view_info.GetAngle(), 0);

    view_info.SetState("lol jk");
    ASSERT_EQ(view_info.GetBaseFrameset().GetSprite(), "windows better than linux");
    ASSERT_EQ(view_info.GetBaseFrameset().GetState(), "lol jk");
    ASSERT_EQ(view_info.GetAngle(), 0);

    view_info.SetAngle(33);
    ASSERT_EQ(view_info.GetBaseFrameset().GetSprite(), "windows better than linux");
    ASSERT_EQ(view_info.GetBaseFrameset().GetState(), "lol jk");
    ASSERT_EQ(view_info.GetAngle(), 33);
}








