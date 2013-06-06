/**
 * Copyright (C) 2011-2013 Paul Wortmann, PhysHex Games, www.physhexgames.co.nr
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

#include "window_manager.hpp"
#include "../game.hpp"

extern game_class         game;

//--------------------------------------------------------- Window Manager Class -------------------------------------------------------------------

window_manager_class::window_manager_class(void)
{
    window_manager_class::event.id             = 0;
    window_manager_class::number_of_windows    = 0;
    window_manager_class::windows_list_created = false;
}

window_manager_class::~window_manager_class(void)
{

}

bool  window_manager_class::mouse_over_window(float wx, float wy, float ww, float wh)
{
    float mx = window_manager_class::mouse_x;
    float my = window_manager_class::mouse_y;
    if ((mx > (wx-(ww/2))) && (mx < (wx+(ww/2))) && (my > (wy-(wh/2))) && (my < (wy+(wh/2)))) return(true);
    else return(false);
};

int  window_manager_class::mouse_over_window(void)
{
    int return_value = MOUSE_OVER_MAP;
    for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
    {
        if (window_manager_class::window[window_manager_class::window_stack[window_count]].enabled)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].mouse_over_menu)
            {
                return_value = window_manager_class::window[window_manager_class::window_stack[window_count]].UID;
            }
        }
    }
    return (return_value);
};

int window_manager_class::mouse_over_element(int UID)
{
    int window_count = 0;
    int return_value = MOUSE_OVER_MAP;
    if (window_manager_class::number_of_windows > 0) // only processed if there are actually windows in the list.
    {
        for (int window_count_2 = 0; window_count_2 < window_manager_class::number_of_windows; window_count_2++)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count_2]].UID == UID) window_count = window_count_2;
        }
    }
    for (int element_count = 0; element_count < window_manager_class::window[window_manager_class::window_stack[window_count]].number_of_elements; element_count++)
    {
        if (    (window_manager_class::window[window_manager_class::window_stack[window_count]].element[element_count].active)
            && (!window_manager_class::window[window_manager_class::window_stack[window_count]].element[element_count].drag_active))
        {
            /* -- test nwm
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].element[element_count].mouse_over_element())
            {
                return_value = element_count;
            }
            */
        }
    }
    return (return_value);
};

void window_manager_class::window_stack_sort(void)
{
    if (!window_manager_class::element_drag_in_progress)
    {
        if (window_manager_class::number_of_windows > 1) // only processed if there are actually windows in the list to sort.
        {
            for (int window_count = window_manager_class::number_of_windows-1; window_count >= 1; window_count--)
            {
                if ((window_manager_class::window[window_manager_class::window_stack[window_count]].active) && (!window_manager_class::window[window_manager_class::window_stack[window_count]].set_behind))
                {
                    int temp_window_count = window_manager_class::window_stack[window_count-1];
                    window_manager_class::window_stack[window_count-1] = window_manager_class::window_stack[window_count];
                    window_manager_class::window_stack[window_count]   = temp_window_count;
                }
            }
        }
    }
};

void window_manager_class::create_windows(int number_windows)
{
    if (!window_manager_class::windows_list_created)
    {
        // create the windows
        window_manager_class::number_of_windows = number_windows;
        window_manager_class::window = new window_class[window_manager_class::number_of_windows+1];
        // create the window stack
        window_manager_class::window_stack = new int[window_manager_class::number_of_windows+1];
        window_manager_class::windows_list_created = true;
        // Clear the window stack
        for (int window_stack_count = 0; window_stack_count < window_manager_class::number_of_windows; window_stack_count++)
        {
            window_manager_class::window_stack[window_stack_count] = -1;
        }
    }
 }

int  window_manager_class::window_get_number(int UID)
{
    int return_value = 0;
    if (window_manager_class::number_of_windows > 0) // only processed if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].UID == UID) return_value = window_manager_class::window_stack[window_count];
        }
    }
    return(return_value);
};

void window_manager_class::window_set_active(int UID)
{
    if (window_manager_class::number_of_windows > 0) // only processed if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].UID == UID)
            {
                window_manager_class::window[window_manager_class::window_stack[window_count]].active = true;
            }
            else
            {
                window_manager_class::window[window_manager_class::window_stack[window_count]].active = false;
            }
        }
    }
    window_manager_class::event.id = EVENT_WINDOW_STACK_SORT; // request stack sort
};

void window_manager_class::window_set_inactive(int UID)
{
    if (window_manager_class::number_of_windows > 0) // only processed if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].UID == UID)
            {
                window_manager_class::window[window_manager_class::window_stack[window_count]].active = false;
            }
        }
    }
    window_manager_class::event.id = EVENT_WINDOW_STACK_SORT; // request stack sort
};

int  window_manager_class::window_get_active(void)
{
    int return_value = 0;
    if (window_manager_class::number_of_windows > 0) // only processed if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if(window_manager_class::window[window_manager_class::window_stack[window_count]].active) return_value = window_manager_class::window[window_manager_class::window_stack[window_count]].UID;
        }
    }
    return(return_value);
};

int window_manager_class::window_register(int UID)
{
    bool window_added = false;
    if (window_manager_class::number_of_windows > 0) // only process windows if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if ((window_manager_class::window[window_count].UID == -1) && (!window_added))
            {
                window_added = true;
                window_manager_class::window[window_count].UID         = UID;
                window_manager_class::window[window_count].active      = false;
                window_manager_class::window[window_count].enabled     = false;
                window_manager_class::window_stack[window_count]       = window_count;
            }
        }
    }
    if(window_added) return(UID);
    else return(-1);
}

int  window_manager_class::window_register(int UID_minimum, int UID_maximum)
{
    int   new_UID   = -1;
    int   temp_UID  = UID_minimum;
    bool  UID_found = false;
    while ((new_UID == -1) and (temp_UID < UID_maximum))
    {
        UID_found = false;
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if (window_manager_class::window[window_count].UID == temp_UID) UID_found = true;
        }
        if (!UID_found) new_UID = temp_UID;
        else temp_UID++;
    }
    if(new_UID > 0) return(window_manager_class::window_register(new_UID));
    else return(-1);
}

void window_manager_class::window_de_register(int UID)
{
    if (window_manager_class::number_of_windows > 0) // only process windows if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].UID == UID)
            {
                window_manager_class::window[window_manager_class::window_stack[window_count]].active  = false;
                window_manager_class::window[window_manager_class::window_stack[window_count]].enabled = false;
                window_manager_class::window[window_manager_class::window_stack[window_count]].UID     = -1;
                window_manager_class::window_stack[window_count] = -1;
            }
        }
    }
}

void window_manager_class::window_enable(int UID)
{
    if (window_manager_class::number_of_windows > 0) // only process windows if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].UID == UID)
            {
                window_manager_class::window[window_manager_class::window_stack[window_count]].enabled = true;
                window_manager_class::window_set_active(window_manager_class::window[window_manager_class::window_stack[window_count]].UID);
                game.window_manager.window_stack_sort();
            }
        }
    }
};

void window_manager_class::window_disable(int UID)
{
    if (window_manager_class::number_of_windows > 0) // only process windows if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].UID == UID)
            {
                window_manager_class::window[window_manager_class::window_stack[window_count]].enabled = false;
                window_manager_class::window_set_inactive(window_manager_class::window[window_manager_class::window_stack[window_count]].UID);
            }
        }
    }
};

void window_manager_class::window_set_pos(int UID_source, int UID_destination)
{
    int source_window      = window_manager_class::window_get_number(UID_source);
    int destination_window = window_manager_class::window_get_number(UID_destination);
    window_manager_class::window[destination_window].set_position(window_manager_class::window[source_window].position.x,window_manager_class::window[source_window].position.y);
};

void window_manager_class::window_transition(int UID_source, int UID_destination)
{
    window_manager_class::window_disable(UID_source);
    window_manager_class::window_set_pos(UID_source,UID_destination);
    window_manager_class::mouse_reset(UID_destination);
    window_manager_class::mouse_reset(UID_source);
    window_manager_class::window_reset_event(UID_destination);
    window_manager_class::window_reset_event(UID_source);
    window_manager_class::window_enable(UID_destination);
    window_manager_class::window_set_active(UID_destination);
    window_manager_class::event.id = EVENT_WINDOW_STACK_SORT; // Request stack sort
    game.core.io.mouse_button_left = false;
};

void window_manager_class::window_reset_event(int UID)
{
    if (window_manager_class::number_of_windows > 0) // only process windows if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].UID == UID)
            {
                window_manager_class::window[window_manager_class::window_stack[window_count]].event.id = EVENT_NONE;
            }
        }
    }
};

void window_manager_class::mouse_reset(int UID)
{
    int window_number;
    if (window_manager_class::number_of_windows > 0) // only process windows if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].UID == UID)
            {
                window_number = window_manager_class::window_stack[window_count];
                window_manager_class::window[window_number].mouse_delay.ready = false;
                window_manager_class::window[window_number].mouse_delay.value = 0;
                for (int element_count = 0; element_count < window_manager_class::window[window_number].number_of_elements; element_count++)
                {
                    window_manager_class::window[window_number].element[element_count].mouse_delay.ready = false;
                    window_manager_class::window[window_number].element[element_count].mouse_delay.value = 0;
                }
            }
        }
    }
};

event_type  window_manager_class::window_get_event(int UID)
{
    event_type return_value;
    return_value.id = 0;
    if (window_manager_class::number_of_windows > 0) // only process windows if there are actually windows in the list.
    {
        for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
        {
            if ((window_manager_class::window[window_manager_class::window_stack[window_count]].UID == UID) && (window_manager_class::window[window_manager_class::window_stack[window_count]].enabled))
            {
                return_value = window_manager_class::window[window_manager_class::window_stack[window_count]].event;
            }
        }
    }
    return(return_value);
};

void window_manager_class::process(void)
{
    //Determine mouse over for overlapping windows.
    bool front_window_found = false;
    event_type temp_event;
    for (int window_count = 0; window_count < window_manager_class::number_of_windows; window_count++)
    {
        if (window_manager_class::window[window_manager_class::window_stack[window_count]].enabled)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].get_mouse_over_menu())
            {
                if (!front_window_found)
                {
                    window_manager_class::window[window_manager_class::window_stack[window_count]].mouse_over_menu  = true;
                    temp_event = window_manager_class::window[window_manager_class::window_stack[window_count]].process(true);
                    if (temp_event.id == EVENT_WINDOW_STACK_SORT) window_manager_class::window_set_active(window_manager_class::window[window_manager_class::window_stack[window_count]].UID);
                    front_window_found = true;
                }
                else
                {
                    window_manager_class::window[window_manager_class::window_stack[window_count]].mouse_over_menu  = true;
                    window_manager_class::window[window_manager_class::window_stack[window_count]].process(false);
                }
            }
            else
            {
                window_manager_class::window[window_manager_class::window_stack[window_count]].process(false);
            }
        }
    }
}

void window_manager_class::render(void)
{
    // Render windows
    if (window_manager_class::number_of_windows > 0) // only processed if there are actually windows in the list.
    {
        for (int window_count = window_manager_class::number_of_windows-1; window_count >= 0; window_count--)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].UID != -1)
            {
                if (window_manager_class::window[window_manager_class::window_stack[window_count]].enabled)
                {
                    window_manager_class::window[window_manager_class::window_stack[window_count]].render();
                }
            }
        }
        // Render dragged items
        for (int window_count = window_manager_class::number_of_windows-1; window_count >= 0; window_count--)
        {
            if (window_manager_class::window[window_manager_class::window_stack[window_count]].UID != -1)
            {
                if (window_manager_class::window[window_manager_class::window_stack[window_count]].enabled)
                {
                    window_manager_class::window[window_manager_class::window_stack[window_count]].render_draged_elements();
                }
            }
        }
    }
}

void swap_elements(int window_src, int element_src, int window_dst, int element_dst)
{
    texture_type *temp_texture_pointer;
    bool allow_swap_elements = true; // test
    if ((window_src == INVENTORY_UID) && (window_dst == INVENTORY_UID)) allow_swap_elements = true;
    if ((window_src == ACTIONBAR_UID) && (window_dst == ACTIONBAR_UID)) allow_swap_elements = true;
    if ((window_src == INVENTORY_UID) && (window_dst == ACTIONBAR_UID)) allow_swap_elements = true;
    if ((window_src == ACTIONBAR_UID) && (window_dst == INVENTORY_UID)) allow_swap_elements = true;
    window_src = game.window_manager.window_get_number(window_src);
    window_dst = game.window_manager.window_get_number(window_dst);
    game.core.log.file_write("Moving element from - ",window_src," - ",element_src," to - ",window_dst," - ",element_dst);
    if ((allow_swap_elements) && ((game.window_manager.window[window_src].element[element_src].type == ITEM)&&(game.window_manager.window[window_dst].element[element_dst].type == ITEM)))
    {
        if    ((game.item_manager.item[(int)game.window_manager.window[window_src].element[element_src].value].type     == game.item_manager.item[(int)game.window_manager.window[window_dst].element[element_dst].value].type)
            && (game.item_manager.item[(int)game.window_manager.window[window_src].element[element_src].value].sub_type == game.item_manager.item[(int)game.window_manager.window[window_dst].element[element_dst].value].sub_type)
            && (game.item_manager.item[(int)game.window_manager.window[window_src].element[element_src].value].quantity_max > 1)
            && (game.item_manager.item[(int)game.window_manager.window[window_dst].element[element_dst].value].quantity_max > 1))
        {
            game.window_manager.window[window_dst].element[element_dst].quantity += game.window_manager.window[window_src].element[element_src].quantity;
            game.window_manager.window[window_src].element[element_src].quantity = 0;
            if (game.window_manager.window[window_dst].element[element_dst].quantity > game.item_manager.item[(int)game.window_manager.window[window_dst].element[element_dst].value].quantity_max)
            {
                game.window_manager.window[window_src].element[element_src].quantity  = game.window_manager.window[window_dst].element[element_dst].quantity - game.item_manager.item[(int)game.window_manager.window[window_dst].element[element_dst].value].quantity_max;
                game.window_manager.window[window_dst].element[element_dst].quantity -= game.item_manager.item[(int)game.window_manager.window[window_dst].element[element_dst].value].quantity_max;
            }
            if (game.window_manager.window[window_src].element[element_src].quantity <= 0)
            {
                game.window_manager.window[window_src].element[element_src].value    = -1;
                game.window_manager.window[window_src].element[element_src].quantity = 0;
            }
        }
       else
        {
            int tmp_value    = game.window_manager.window[window_src].element[element_src].value;
            int tmp_quantity = game.window_manager.window[window_src].element[element_src].quantity;
            game.window_manager.window[window_src].element[element_src].value    = game.window_manager.window[window_dst].element[element_dst].value;
            game.window_manager.window[window_src].element[element_src].quantity = game.window_manager.window[window_dst].element[element_dst].quantity;
            game.window_manager.window[window_dst].element[element_dst].value    = tmp_value;
            game.window_manager.window[window_dst].element[element_dst].quantity = tmp_quantity;
        }
        game.sound_manager.play(game.item_manager.item[(int)game.window_manager.window[window_dst].element[element_dst].value].sound_move);
        temp_texture_pointer = game.window_manager.window[window_src].element[element_src].texture.normal;
        game.window_manager.window[window_src].element[element_src].texture.normal = game.window_manager.window[window_dst].element[element_dst].texture.normal;
        game.window_manager.window[window_dst].element[element_dst].texture.normal = temp_texture_pointer;
    }
};

// ------------------------------------------------------------------------------------------------------------

window_manager_class_2::window_manager_class_2(void)
{
    window_manager_class_2::event.id             = 0;
    window_manager_class_2::number_of_windows    = 0;
}

void window_manager_class_2::process(void)
{
    window_class *temp;
    temp = window_manager_class_2::root;
    while (temp != NULL)
    {
        //temp = temp->next;
    }
};

void window_manager_class_2::render(void)
{

};


/*
class window_manager_class_2
{
    public:
        window_manager_class_2(void);
       ~window_manager_class_2(void);
        int                   number_of_windows;
        window_class         *root;
        window_class         *last;
        int                  *add_window(int type_ID);
        void                  process(void);
        void                  render(void);
};
*/