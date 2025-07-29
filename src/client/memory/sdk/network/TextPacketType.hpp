#pragma once

enum class TextPacketType : int {
    Raw = 0,
    Chat = 1,
    Translate = 2,
    Popup = 3,
    Jukebox = 4,
    Tip = 5,
    SystemMessage = 6,
    Whisper = 7,
    Announcement = 8,
    TextObjectWhisper = 9,
    TextObject = 10,
    TextObjectAnnouncement = 11
};