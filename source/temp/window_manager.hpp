/**
 * Copyright (C) 2011-2012 Paul Wortmann, PhysHex Games, www.physhexgames.co.nr
 * This file is part of "Frost And Flame"
 *
 * "Frost And Flame" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * "Frost And Flame" is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with "Frost And Flame" If not, see <http://www.gnu.org/licenses/>.
 *
 * @author  Paul Wortmann
 * @email   physhex@gmail.com
 * @website www.physhexgames.co.nr
 * @license GPL V3
 * @date 2011-11-11
 */

#ifndef WINDOW_MANAGER_H
#define WINDOW_MANAGER_H

#include "window.hpp"
#include "menu_main.hpp"
#include "menu_game_new.hpp"
#include "menu_game_load.hpp"
#include "menu_game_save.hpp"
#include "menu_options.hpp"

#define    ACTIONBAR_UID          1
#define    PCPROFILE_UID          2
#define    EQUIPMENT_UID          3
#define    QUEST_LOG_UID          4
#define    CHARACTER_UID          5
#define    INVENTORY_UID          6
#define    SPELLBOOK_UID          7
#define    NPCVENDOR_UID          8
#define    MENU_DEFAULT_UID       9  //base menu to store default values, and position / size for conjoined windows. maybe?
#define    MENU_MAIN_UID          10
#define    MENU_GAME_NEW_UID      11
#define    MENU_GAME_SAVE_UID     12
#define    MENU_GAME_LOAD_UID     13
#define    MENU_OPTIONS_UID       14
#define    MENU_GAME_OVER_UID     15
#define    MENU_PAUSE_UID         16

class window_manager_stack_class
{
    public:
        bool active;
        int  UID;
        int  window_number;
        bool enabled;
        window_manager_stack_class(void);
};

class window_manager_class
{
    protected:
    private:
    public:
        int   event;
        float mouse_x;
        float mouse_y;
        int   number_of_windows;
        bool  drag_in_progress;
        bool  windows_list_created;
        window_class *window;
        int  *window_stack;
        window_manager_class(void);
       ~window_manager_class(void);
        void create_windows(int number_windows);
        void window_stack_sort(void);
        int  window_get_number(int UID);
        void window_set_active(int UID);
        void window_set_inactive(int UID);
        int  window_get_event(int UID);
        int  window_get_active(void);
        int  window_register(int UID);
        int  window_register(int UID_minimum, int UID_maximum);
        void window_de_register(int UID);
        void window_enable(int UID);
        void window_disable(int UID);
        void window_set_pos(int UID_destination, int UID_source);
        void window_transition(int UID_destination, int UID_source);
        void window_reset_event(int UID);
        void mouse_reset(int UID);
        bool mouse_over_window(float wx, float wy, float ww, float wh);
        void process(void);
        void render(void);
};

void setup_windows(void);
void process_windows(void);

#endif // WINDOW_MANAGER_H



