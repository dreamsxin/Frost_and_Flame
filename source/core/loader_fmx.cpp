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

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "loader_fmx.hpp"
#include "../game/game.hpp"

extern game_class         game;

void fmx_load(fmx_map_type *fmx_map_pointer, std::string file_name)
{
    game.core.log.file_write("Loading FMX map file -> ",file_name);
    int          position_count  = 0;
    int          position_start  = 0;
    bool         map_data        = true;
    bool         tileset_data    = false;
    bool         layer_data      = false;
    int          tileset_count   = 0;
    int          layer_count     = 0;
    int          tile_count      = 0;
    char         temp_char       = ' ';
    float        temp_float_data;
    int          temp_int_data;
    std::string  temp_string_data;
    std::string  temp_string_key;
    std::string  temp_string_value;
    std::string  data_line;
    fmx_map_pointer->data.number_of_tiles    = 0;
    fmx_map_pointer->data.number_of_tilesets = 0;
    fmx_map_pointer->data.number_of_layers   = 0;
    std::fstream script_file(file_name.c_str(),std::ios::in|std::ios::binary);
    if (script_file.is_open())
    {
        // find size of data and set new array size
        while (script_file.good())
        {
            getline(script_file,data_line);
            {
                position_count = 0;
                if ((data_line[position_count] == ' ') && (data_line.length() > 2))
                {
                    temp_char = ' ';
                    while (temp_char == ' ')
                    {
                        temp_char = data_line[position_count];
                        position_count++;
                    }
                    position_count--;
                }
                position_start = position_count;
                if((data_line[position_count] == '<') && (data_line[position_count+1] == '/') && (data_line.length() > 2))
                {
                    temp_char         = ' ';
                    temp_string_key   = "";
                    temp_string_value = "";
                    while(temp_char != '>')
                    {
                        temp_char = data_line[position_count];
                        if((temp_char != '<') && (temp_char != '/') && (temp_char != '>'))
                        {
                            temp_string_key += temp_char;
                        }
                        position_count++;
                        if(position_count > (int)data_line.length()) temp_char = '>';
                    }
                    if (temp_string_key == "tileset")
                    {
                        tileset_count++;
                    }
                }
                position_count = position_start;
                if((data_line[position_count] == '<') && (data_line[position_count+1] != '/') && (data_line.length() > 2))
                {
                    position_count++;
                    while(position_count < (int)data_line.length())
                    {
                        temp_char         = ' ';
                        temp_string_key   = "";
                        temp_string_value = "";
                        while(temp_char != '"')
                        {
                            temp_char = data_line[position_count];
                            if((temp_char != '"') && (temp_char != '='))
                            {
                                if((data_line[position_count-1] != '"') && (temp_char == ' ')) temp_string_key += temp_char;
                                else if (temp_char != ' ') temp_string_key += temp_char;
                            }
                            position_count++;
                            if(position_count > (int)data_line.length()) temp_char = '"';
                        }
                        temp_char        = ' ';
                        while(temp_char != '"')
                        {
                            temp_char = data_line[position_count];
                            if(temp_char != '"') temp_string_value += temp_char;
                            position_count++;
                            if(position_count > (int)data_line.length()) (temp_char = '"');
                        }
                        temp_string_data    = temp_string_value.c_str();
                        temp_float_data     = atof(temp_string_value.c_str());
                        temp_int_data       = atoi(temp_string_value.c_str());
                        if (temp_string_key == "map version")      map_data     = true;
                        if (map_data)
                        {
                            if (temp_string_key == "width")       fmx_map_pointer->data.map_width  = temp_int_data;
                            if (temp_string_key == "height")      fmx_map_pointer->data.map_height = temp_int_data;
                            if (temp_string_key == "tileheight")  map_data                         = false;
                        }
                        if (temp_string_key == "layer name")      fmx_map_pointer->data.number_of_layers++;
                    }
                }
            }
        }
        fmx_map_pointer->data.number_of_tiles    = fmx_map_pointer->data.map_width * fmx_map_pointer->data.map_height;
        fmx_map_pointer->data.number_of_tilesets = tileset_count;
        script_file.clear();
        script_file.seekg(0, std::ios::beg);
        fmx_map_pointer->tileset      = new fmx_tileset_type[fmx_map_pointer->data.number_of_tilesets+1];
        fmx_map_pointer->layer        = new fmx_layer_type  [fmx_map_pointer->data.number_of_layers+1];
        for(layer_count = 0; layer_count <= fmx_map_pointer->data.number_of_layers; layer_count++)
        {
            fmx_map_pointer->layer[layer_count].tile = new fmx_tile_type   [fmx_map_pointer->data.number_of_tiles+1];
        }
        position_count                           = 0;
        position_start                           = 0;
        map_data                                 = true;
        tileset_data                             = false;
        layer_data                               = false;
        tileset_count                            = 0;
        layer_count                              = 0;
        tile_count                               = 0;
        temp_char                                = ' ';
        fmx_map_pointer->data.number_of_tiles    = 0;
        fmx_map_pointer->data.number_of_tilesets = 0;
        // load data
        while (script_file.good())
        {
            getline(script_file,data_line);
            {
                position_count = 0;
                if ((data_line[position_count] == ' ') && (data_line.length() > 2))
                {
                    temp_char = ' ';
                    while (temp_char == ' ')
                    {
                        temp_char = data_line[position_count];
                        position_count++;
                    }
                    position_count--;
                }
                position_start = position_count;
                if((data_line[position_count] == '<') && (data_line[position_count+1] == '/') && (data_line.length() > 2))
                {
                    temp_char         = ' ';
                    temp_string_key   = "";
                    temp_string_value = "";
                    while(temp_char != '>')
                    {
                        temp_char = data_line[position_count];
                        if((temp_char != '<') && (temp_char != '/') && (temp_char != '>'))
                        {
                            temp_string_key += temp_char;
                        }
                        position_count++;
                        if(position_count > (int)data_line.length()) temp_char = '>';
                    }
                    if (temp_string_key == "tileset")
                    {
                        fmx_map_pointer->tileset[tileset_count].number_of_tiles = ((fmx_map_pointer->tileset[tileset_count].image_width / fmx_map_pointer->tileset[tileset_count].tile_width) * (fmx_map_pointer->tileset[tileset_count].image_height / fmx_map_pointer->tileset[tileset_count].tile_height));
                        tileset_data = false;
                        tileset_count++;
                    }
                    if (temp_string_key == "layer")
                    {
                        tile_count      = 0;
                        layer_data      = false;
                        layer_count++;
                    }
                }
                position_count = position_start;
                if((data_line[position_count] == '<') && (data_line[position_count+1] != '/') && (data_line.length() > 2))
                {
                    position_count++;
                    while(position_count < (int)data_line.length())
                    {
                        temp_char         = ' ';
                        temp_string_key   = "";
                        temp_string_value = "";
                        while(temp_char != '"')
                        {
                            temp_char = data_line[position_count];
                            if((temp_char != '"') && (temp_char != '='))
                            {
                                if((data_line[position_count-1] != '"') && (temp_char == ' ')) temp_string_key += temp_char;
                                else if (temp_char != ' ') temp_string_key += temp_char;
                            }
                            position_count++;
                            if(position_count > (int)data_line.length()) temp_char = '"';
                        }
                        temp_char        = ' ';
                        while(temp_char != '"')
                        {
                            temp_char = data_line[position_count];
                            if(temp_char != '"') temp_string_value += temp_char;
                            position_count++;
                            if(position_count > (int)data_line.length()) (temp_char = '"');
                        }
                        temp_string_data    = temp_string_value.c_str();
                        temp_float_data     = atof(temp_string_value.c_str());
                        temp_int_data       = atoi(temp_string_value.c_str());
                        if (temp_string_key == "map version")      map_data     = true;
                        if (temp_string_key == "tileset firstgid") tileset_data = true;
                        if (temp_string_key == "layer name")       layer_data   = true;
                        if (map_data)
                        {
                            if (temp_string_key == "?xml version") fmx_map_pointer->data.xml_version     = temp_float_data;
                            if (temp_string_key == "map version")  fmx_map_pointer->data.map_version     = temp_float_data;
                            if (temp_string_key == "encoding")     fmx_map_pointer->data.xml_encoding    = temp_string_data;
                            if (temp_string_key == "orientation")  fmx_map_pointer->data.map_orientation = temp_string_data;
                            if (temp_string_key == "width")        fmx_map_pointer->data.map_width       = temp_int_data;
                            if (temp_string_key == "height")       fmx_map_pointer->data.map_height      = temp_int_data;
                            if (temp_string_key == "tilewidth")    fmx_map_pointer->data.map_tile_width  = temp_int_data;
                            if (temp_string_key == "tileheight")   fmx_map_pointer->data.map_tile_height = temp_int_data;
                            if (temp_string_key == "tileheight")   map_data                              = false;
                        }
                        if (tileset_data)
                        {
                            if (temp_string_key == "tileset firstgid") fmx_map_pointer->tileset[tileset_count].first_gid    = temp_int_data;
                            if (temp_string_key == "name")             fmx_map_pointer->tileset[tileset_count].image_name   = temp_string_data;
                            if (temp_string_key == "tilewidth")        fmx_map_pointer->tileset[tileset_count].tile_width   = temp_int_data;
                            if (temp_string_key == "tileheight")       fmx_map_pointer->tileset[tileset_count].tile_height  = temp_int_data;
                            if (temp_string_key == "image source")     fmx_map_pointer->tileset[tileset_count].image_source = temp_string_data;
                            if (temp_string_key == "width")            fmx_map_pointer->tileset[tileset_count].image_width  = temp_int_data;
                            if (temp_string_key == "height")           fmx_map_pointer->tileset[tileset_count].image_height = temp_int_data;
                        }
                        if (layer_data)
                        {
                            if (temp_string_key == "layer name") tile_count      = 0;
                            if (temp_string_key == "width")      fmx_map_pointer->layer[layer_count].width  = temp_int_data;
                            if (temp_string_key == "height")     fmx_map_pointer->layer[layer_count].height = temp_int_data;
                            if (temp_string_key == "tile gid")
                            {
                                fmx_map_pointer->layer[layer_count].tile[tile_count].tile_tileset = 0;
                                for (int temp_tileset_count = 0; temp_tileset_count < tileset_count; temp_tileset_count++)
                                {
                                    if (temp_int_data >= fmx_map_pointer->tileset[temp_tileset_count].first_gid)
                                    {
                                        fmx_map_pointer->layer[layer_count].tile[tile_count].tile_tileset = temp_tileset_count;
                                    }
                                }
                                temp_int_data -= fmx_map_pointer->tileset[fmx_map_pointer->layer[layer_count].tile[tile_count].tile_tileset].first_gid;
                                temp_int_data += 1;
                                fmx_map_pointer->layer[layer_count].tile[tile_count].tile         = temp_int_data;
                                fmx_map_pointer->layer[layer_count].tile[tile_count].collision    = false;
                                tile_count++;
                            }
                        }
                    }
                }
            }
        }
        script_file.close();
        fmx_map_pointer->data.number_of_tiles    = fmx_map_pointer->data.map_width * fmx_map_pointer->data.map_height;
        fmx_map_pointer->data.number_of_tilesets = tileset_count;
        fmx_map_pointer->data.number_of_layers   = layer_count;
        for (int tileset_number = 0; tileset_number < fmx_map_pointer->data.number_of_tilesets; tileset_number++)
        {
            fmx_map_pointer->tileset[tileset_number].image_source    = game.core.file.path_remove(fmx_map_pointer->tileset[tileset_number].image_source);
            fmx_map_pointer->tileset[tileset_number].image_source    = game.core.file.path_add(fmx_map_pointer->tileset[tileset_number].image_source,"data/tilesets/");
            fmx_map_pointer->tileset[tileset_number].tile            = game.texture_manager.add_texture(fmx_map_pointer->tileset[tileset_number].image_source.c_str(),true,fmx_map_pointer->tileset[tileset_number].tile_width,fmx_map_pointer->tileset[tileset_number].tile_height);
            fmx_map_pointer->tileset[tileset_number].number_of_tiles = fmx_map_pointer->tileset[tileset_number].tile->data.frame_max;
        }
    }
    else game.core.log.file_write("Unable to load FMX map file -> ",file_name);
};

void fmx_save(fmx_map_type *fmx_map_pointer, std::string file_name)
{
    std::fstream script_file(file_name.c_str(),std::ios::out|std::ios::binary|std::ios::trunc);
    if (script_file.is_open())
    {
        script_file << "<?xml version=";
        script_file << '"';
        script_file << (float)fmx_map_pointer->data.xml_version;
        if ((float)fmx_map_pointer->data.xml_version == (int)fmx_map_pointer->data.xml_version) script_file << ".0";
        script_file << '"';
        script_file << " encoding=";
        script_file << '"';
        script_file << fmx_map_pointer->data.xml_encoding.c_str();
        script_file << '"';
        script_file << "?>";
        script_file << "\n";

        script_file << "<map version=";
        script_file << '"';
        script_file << (float)fmx_map_pointer->data.map_version;
        if ((float)fmx_map_pointer->data.map_version == (int)fmx_map_pointer->data.map_version) script_file << ".0";
        script_file << '"';
        script_file << " orientation=";
        script_file << '"';
        script_file << fmx_map_pointer->data.map_orientation.c_str();
        script_file << '"';
        script_file << " width=";
        script_file << '"';
        script_file << fmx_map_pointer->data.map_width;
        script_file << '"';
        script_file << " height=";
        script_file << '"';
        script_file << fmx_map_pointer->data.map_height;
        script_file << '"';
        script_file << " tilewidth=";
        script_file << '"';
        script_file << fmx_map_pointer->data.map_tile_width;
        script_file << '"';
        script_file << " tileheight=";
        script_file << '"';
        script_file << fmx_map_pointer->data.map_tile_height;
        script_file << '"';
        script_file << ">";
        script_file << "\n";

        script_file << " <properties>";
        script_file << "\n";
        script_file << "  <property name=";
        script_file << '"';
        script_file << "MAP_ID";
        script_file << '"';
        script_file << " value=";
        script_file << '"';
        script_file << "0";
        script_file << '"';
        script_file << "/>";
        script_file << "\n";
        script_file << " </properties>";
        script_file << "\n";

        for (int tileset_count = 0; tileset_count < fmx_map_pointer->data.number_of_tilesets; tileset_count++)
        {
            script_file << " <tileset firstgid=";
            script_file << '"';
            script_file << fmx_map_pointer->tileset[tileset_count].first_gid;
            script_file << '"';
            script_file << " name=";
            script_file << '"';
            script_file << fmx_map_pointer->tileset[tileset_count].image_name;
            script_file << '"';
            script_file << " tilewidth=";
            script_file << '"';
            script_file << fmx_map_pointer->tileset[tileset_count].tile_width;
            script_file << '"';
            script_file << " tileheight=";
            script_file << '"';
            script_file << fmx_map_pointer->tileset[tileset_count].tile_height;
            script_file << '"';
            script_file << ">";
            script_file << "\n";
            script_file << "  <image source=";
            script_file << '"';
            script_file << fmx_map_pointer->tileset[tileset_count].image_source;
            script_file << '"';
            script_file << " width=";
            script_file << '"';
            script_file << fmx_map_pointer->tileset[tileset_count].image_width;
            script_file << '"';
            script_file << " height=";
            script_file << '"';
            script_file << fmx_map_pointer->tileset[tileset_count].image_height;
            script_file << '"';
            script_file << "/>";
            script_file << "\n";
            script_file << " </tileset>";
            script_file << "\n";
        }
        for (int layer_count = 0; layer_count < fmx_map_pointer->data.number_of_layers; layer_count++)
        {
            script_file << " <layer name=";
            script_file << '"';
            script_file << "tile";
            script_file << '"';
            script_file << " width=";
            script_file << '"';
            script_file << fmx_map_pointer->layer[layer_count].width;
            script_file << '"';
            script_file << " height=";
            script_file << '"';
            script_file << fmx_map_pointer->layer[layer_count].height;
            script_file << '"';
            script_file << ">";
            script_file << "\n";
            script_file << "  <data>";
            script_file << "\n";
            for (int tile_count = 0; tile_count < fmx_map_pointer->data.number_of_tiles; tile_count++)
            {
                script_file << "   <tile gid=";
                script_file << '"';
                script_file << ((fmx_map_pointer->layer[layer_count].tile[tile_count].tile + fmx_map_pointer->tileset[fmx_map_pointer->layer[layer_count].tile[tile_count].tile_tileset].first_gid) - 1);
                script_file << '"';
                script_file << "/>";
                script_file << "\n";
            }
            script_file << "  </data>";
            script_file << "\n";
            script_file << " </layer>";
            script_file << "\n";
        }
        script_file << "</map>";
        script_file << "\n";
        script_file.close();
    }
};
