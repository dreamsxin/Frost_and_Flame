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

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H

#include <GL/gl.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <string>

#define GL_BGR  0x80E0
#define GL_BGRA 0x80E1

#define DEFAULT_FRAME_WIDTH     64
#define DEFAULT_FRAME_HEIGHT    32

struct frame_type
{
    bool      active;
    GLuint    data;
};

struct texture_type
{
    bool             loaded;
    bool             sprite_sheet;
    std::string      path;
    int              width;
    int              height;
    bool             rotate_able;
    float            rotate_speed;
    int              rotate_direction;
    float            angle;
    float            frame_delay;
    float            frame_delay_count;
    float            frame_delay_max;
    int              frame_number;
    int              frame_max;
    frame_type*      frame;
    texture_type    *next;
};

class texture_manager_class
{
    public:
        texture_manager_class(void);
       ~texture_manager_class(void);
        int           number_of_textures;
        texture_type *root;
        texture_type *last;
        texture_type *add_texture(std::string file_name);
        texture_type *add_texture(std::string file_name, bool is_sprite_sheet);
        texture_type *add_texture(std::string file_name, bool is_sprite_sheet, int width_set, int height_set);
        void          load_textures(void);
        void          reload_textures(void);
        bool          load_texture(texture_type *texure);
        bool          load_sprite_sheet(texture_type *texure);
        bool          load_sprite_sheet(texture_type *texure, int width_set, int height_set);
        void          bind_image(texture_type *texure);
        void          process(texture_type *texure);
        void          draw(texture_type *texure, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set);
        void          draw(texture_type *texure, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, int   angle_set);
        void          draw(texture_type *texure, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, float angle_set);
        void          draw(texture_type *texure, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, float angle_set, float alpha);
        void          draw(texture_type *texure, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, float angle_set, float red, float green, float blue, float alpha);
        void          draw(texture_type *texure, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, float angle_set, float red, float green, float blue, float alpha, int frame_set);
        void          draw(texture_type *texure, bool rumble_set, float pos_x, float pos_y, float pos_z, float width_set, float height_set, float angle_set, int frame_set);
};

#endif // TEXTURE_MANAGER_H
