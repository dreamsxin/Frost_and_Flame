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

#include "menu_main.hpp"
#include "../game.hpp"

extern game_class         game;

//----------------------------------------------------------Main menu Class ------------------------------------------------------------------------

void setup_inventory_window(int UID)
{
    int window_number = game.window_manager.window_get_number(UID);
    int element_number = 0;
    game.window_manager.window[window_number].UID                     = UID;
    game.window_manager.window[window_number].active                  = false;
    game.window_manager.window[window_number].mouse_over_menu         = false;
    game.window_manager.window[window_number].mouse_over_title        = false;
    game.window_manager.window[window_number].position.x              = 0.0f;
    game.window_manager.window[window_number].position.y              = 0.0f;
    game.window_manager.window[window_number].position.z              = 0.0f;
    game.window_manager.window[window_number].size.x                  = 0.5f;
    game.window_manager.window[window_number].size.y                  = game.window_manager.window[window_number].size.x * 2.5f;
    game.window_manager.window[window_number].texture.angle           = 0.0f;
    game.window_manager.window[window_number].texture.base                = game.texture_manager.add_texture("data/textures/UI/menu/inventory_background.png");
    game.window_manager.window[window_number].texture.normal              = game.texture_manager.add_texture("data/textures/UI/menu/button_normal.png");
    game.window_manager.window[window_number].texture.highlighted         = game.texture_manager.add_texture("data/textures/UI/menu/button_highlighted.png");
    game.window_manager.window[window_number].texture.disabled            = game.texture_manager.add_texture("data/textures/UI/menu/button_disabled.png");
    game.window_manager.window[window_number].sound.on_click.enabled      = true;
    game.window_manager.window[window_number].sound.on_click.sound        = game.sound_manager.add_sound("data/sound/menu/menu_select_00.wav");
    game.window_manager.window[window_number].sound.on_mouse_over.enabled = true;
    game.window_manager.window[window_number].sound.on_mouse_over.sound   = game.sound_manager.add_sound("data/sound/menu/menu_move_00.wav");
    game.window_manager.window[window_number].font                        = game.font_manager.add_font("data/fonts/font_001.ttf");
    game.window_manager.window[window_number].mouse_delay.maximum     = 30;
    game.window_manager.window[window_number].event.id                = 0;
    game.window_manager.window[window_number].color.normal.r          = 128;
    game.window_manager.window[window_number].color.normal.b          = 128;
    game.window_manager.window[window_number].color.normal.g          = 128;
    game.window_manager.window[window_number].color.normal.a          = 255;
    game.window_manager.window[window_number].color.highlighted.r     = 192;
    game.window_manager.window[window_number].color.highlighted.b     = 192;
    game.window_manager.window[window_number].color.highlighted.g     = 192;
    game.window_manager.window[window_number].color.highlighted.a     = 255;
    game.window_manager.window[window_number].color.disabled.r        = 064;
    game.window_manager.window[window_number].color.disabled.b        = 064;
    game.window_manager.window[window_number].color.disabled.g        = 064;
    game.window_manager.window[window_number].color.disabled.a        = 128;
    game.window_manager.window[window_number].zoom.enabled            = true;
    game.window_manager.window[window_number].zoom.maximum            = 0.02f;
    game.window_manager.window[window_number].zoom.speed              = 0.004f;
    game.window_manager.window[window_number].texture.angle           = 0.0f;
    game.window_manager.window[window_number].title.text              = "Inventory";
    game.window_manager.window[window_number].title.enabled           = true;
    game.window_manager.window[window_number].title.size.x            = game.window_manager.window[window_number].title.text.length()/1.2f;
    game.window_manager.window[window_number].title.size.y            = game.window_manager.window[window_number].title.size.x*4;
    game.window_manager.window[window_number].title.position.x        = game.window_manager.window[window_number].position.x - (game.window_manager.window[window_number].title.size.x/100.0f);
    game.window_manager.window[window_number].title.position.y        = game.window_manager.window[window_number].position.y + (game.window_manager.window[window_number].size.y/2.0f) - (game.window_manager.window[window_number].title.size.y / 380.0f);
    game.window_manager.window[window_number].title_bar.size.x        = game.window_manager.window[window_number].size.x; // x/2.0f for middle section
    game.window_manager.window[window_number].title_bar.size.y        = game.window_manager.window[window_number].size.y / 10.0f;
    game.window_manager.window[window_number].title_bar.position.x    = game.window_manager.window[window_number].position.x;
    game.window_manager.window[window_number].title_bar.position.y    = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/2.0f)-(game.window_manager.window[window_number].title_bar.size.y/2.0f);

    // ---------------------------- Setup window elements ----------------------------------------------------
    game.window_manager.window[window_number].number_of_elements = 49;
    game.window_manager.window[window_number].element = new window_element_class[game.window_manager.window[window_number].number_of_elements];
    element_number = 0; //--- Close button ---
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = BUTTON;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.1f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.1f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/2.0f)-(game.window_manager.window[window_number].element[element_number].size.x/1.8f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].title.position.y+(game.window_manager.window[window_number].element[element_number].size.y/8.0f);
    game.window_manager.window[window_number].element[element_number].texture.normal              = game.texture_manager.add_texture("data/textures/UI/menu/close_button.png");
    game.window_manager.window[window_number].element[element_number].texture.highlighted         = game.texture_manager.add_texture("data/textures/UI/menu/close_button_highlighted.png");
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 1; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/2.82f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/3.26f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 2; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/4.72f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/3.26f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 3; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/14.62f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/3.26f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 4; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/14.02f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/3.26f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 5; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/4.64f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/3.26f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 6; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/2.80f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/3.26f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;

    element_number = 7; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/2.82f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/4.66f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 8; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/4.72f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/4.66f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 9; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/14.62f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/4.66f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 10; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/14.02f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/4.66f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 11; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/4.64f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/4.66f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 12; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/2.80f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/4.66f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;

    element_number = 13; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/2.82f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/8.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 14; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/4.72f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/8.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 15; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/14.62f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/8.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 16; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/14.02f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/8.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 17; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/4.64f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/8.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 18; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/2.80f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/8.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;

    element_number = 19; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/2.82f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/32.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 20; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/4.72f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/32.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 21; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/14.62f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/32.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 22; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/14.02f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/32.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 23; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/4.64f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/32.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 24; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/2.80f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y+(game.window_manager.window[window_number].size.y/32.10f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;

    element_number = 25; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/2.82f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/16.80f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 26; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/4.72f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/16.80f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 27; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/14.62f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/16.80f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 28; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/14.02f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/16.80f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 29; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/4.64f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/16.80f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 30; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/2.80f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/16.80f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;

    element_number = 31; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/2.82f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/6.56f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 32; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/4.72f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/6.56f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 33; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/14.62f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/6.56f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 34; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/14.02f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/6.56f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 35; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/4.64f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/6.56f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 36; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/2.80f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/6.56f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;

    element_number = 37; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/2.82f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/4.08f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 38; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/4.72f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/4.08f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 39; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/14.62f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/4.08f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 40; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/14.02f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/4.08f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 41; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/4.64f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/4.08f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 42; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/2.80f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/4.08f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;

    element_number = 43; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/2.82f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/2.98f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 44; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/4.72f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/2.98f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 45; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x-(game.window_manager.window[window_number].size.x/14.62f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/2.98f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 46; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/14.02f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/2.98f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 47; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/4.64f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/2.98f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
    element_number = 48; //--- Inventory cell
    game.window_manager.window[window_number].element[element_number].window_UID                  = game.window_manager.window[window_number].UID;
    game.window_manager.window[window_number].element[element_number].element_UID                 = element_number;
    game.window_manager.window[window_number].element[element_number].title.text                  = "";
    game.window_manager.window[window_number].element[element_number].title.enabled               = false;
    game.window_manager.window[window_number].element[element_number].dragable                    = true;
    game.window_manager.window[window_number].element[element_number].active                      = true;
    game.window_manager.window[window_number].element[element_number].type                        = ITEM;
    game.window_manager.window[window_number].element[element_number].zoom.enabled                = false;
    game.window_manager.window[window_number].element[element_number].value                       = -1;
    game.window_manager.window[window_number].element[element_number].color                       = game.window_manager.window[window_number].color;
    game.window_manager.window[window_number].element[element_number].size.x                      = 0.050f;
    game.window_manager.window[window_number].element[element_number].size.y                      = 0.085f;
    game.window_manager.window[window_number].element[element_number].position.x                  = game.window_manager.window[window_number].position.x+(game.window_manager.window[window_number].size.x/2.80f);
    game.window_manager.window[window_number].element[element_number].position.y                  = game.window_manager.window[window_number].position.y-(game.window_manager.window[window_number].size.y/2.98f);
    game.window_manager.window[window_number].element[element_number].sound                       = game.window_manager.window[window_number].sound;
    game.window_manager.window[window_number].element[element_number].sound.on_click.enabled      = false;
    game.window_manager.window[window_number].element[element_number].sound.on_mouse_over.enabled = false;
    game.window_manager.window[window_number].element[element_number].mouse_delay.maximum         = 30;
    game.window_manager.window[window_number].element[element_number].font                        = game.window_manager.window[window_number].font;
};

void process_inventory_window(int window_number)
{
    if (game.window_manager.window[window_number].event.id > EVENT_NONE)
    {
        switch (game.window_manager.window[window_number].event.id)
        {
            case ((0*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Close menu button
                game.window_manager.window_disable(INVENTORY_UID);
                game.core.inventory_active= false;
            break;
            case (EVENT_WINDOW_STACK_SORT): //Window stack sort
                game.window_manager.window_stack_sort();
                game.window_manager.event.id = EVENT_NONE;
            break;
            case (EVENT_ELEMENT_DRAG): //Element drag event posted
                //game.window_manager.source.window = INVENTORY_UID;
            break;
            case (EVENT_ELEMENT_DROP): //Element drop event posted
                //game.window_manager.destination.window = INVENTORY_UID;
            break;
            case ((1*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((1*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,1);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((2*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((2*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,2);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((3*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((3*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,3);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((4*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((4*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,4);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((5*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((5*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,5);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((6*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((6*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,6);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((7*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((7*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,7);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((8*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((8*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,8);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((9*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((9*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,9);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((10*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((10*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,10);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((11*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((11*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,11);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((12*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((12*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,12);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((13*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((13*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,13);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((14*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((14*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,14);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((15*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((15*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,15);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((16*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((16*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,16);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((17*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((17*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,17);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((18*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((18*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,18);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((19*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((19*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,19);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((20*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((20*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,20);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((21*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((21*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,21);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((22*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((22*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,22);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((23*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((23*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,23);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((24*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((24*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,24);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((25*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((25*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,25);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((26*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((26*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,26);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((27*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((27*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,27);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((28*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((28*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,28);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((29*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((29*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,29);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((30*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((30*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,30);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((31*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((31*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,31);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((32*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((32*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,32);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((33*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((33*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,33);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((34*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((34*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,34);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((35*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((35*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,35);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((36*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((36*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,36);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((37*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((37*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,37);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((38*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((38*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,38);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((39*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((39*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,39);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((40*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((40*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,40);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((41*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((41*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,41);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((42*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((42*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,42);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((43*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((43*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,43);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((44*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((44*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,44);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((45*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((45*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,45);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((46*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((46*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,46);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((47*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((47*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,47);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((48*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_LEFT): // Process item 0
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            case ((48*EVENT_BUTTON_MULTIPLIER)+EVENT_ELEMENT_MOUSE_RIGHT): // Process item 0
                use_item(window_number,48);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
            default:
                game.core.log.file_write("Unable to process event - ",game.window_manager.window[window_number].event.id, " - UID - ",game.window_manager.window[window_number].UID);
                game.window_manager.window[window_number].event.id = EVENT_NONE;
            break;
        }
    }
    game.window_manager.window[window_number].event.id = EVENT_NONE;
};

