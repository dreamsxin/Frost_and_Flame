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

#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "loader_fmx.hpp"

struct path_node_type
{
    int             tile_start_x;
    int             tile_start_y;
    int             tile_end_x;
    int             tile_end_y;
    int             tile_x;
    int             tile_y;
    bool            end_found;
    bool            closed_list;
    int             F;
    int             G;
    int             H;
    path_node_type* parent;
    path_node_type* node_1;
    path_node_type* node_2;
    path_node_type* node_3;
    path_node_type* node_4;
    path_node_type* node_5;
    path_node_type* node_6;
    path_node_type* node_7;
    path_node_type* node_8;
};

struct path_type
{
    int       tile_start;
    int       tile_end;
    int       tile_current;
    int       path_length;
    int*      path_data;
};

void map_path_reset (fmx_map_type *fmx_map_pointer);
int  map_distance_H (fmx_map_type *fmx_map_pointer, int tile_current, int tile_end);
int  map_distance_G (fmx_map_type *fmx_map_pointer, int tile_current);
int  map_tile_calc  (fmx_map_type *fmx_map_pointer, int tile_current, int tile_parent, int tile_end);
path_type* map_path_find (fmx_map_type *fmx_map_pointer, int position_1_x, int position_1_y, int position_2_x, int position_2_y);
path_type* map_path_find (fmx_map_type *fmx_map_pointer, int tile_1, int tile_2);


path_type*      _map_path_find(fmx_map_type *fmx_map_pointer, int position_1_x, int position_1_y, int position_2_x, int position_2_y);
path_node_type* map_path_find_internal_calc(fmx_map_type *fmx_map_pointer, path_node_type* parent_node_pointer, int position_1_x, int position_1_y);
path_type*      map_path_find_internal(fmx_map_type *fmx_map_pointer, path_node_type* path_node_pointer, int position_1_x, int position_1_y);

#endif //PATHFINDING_H
