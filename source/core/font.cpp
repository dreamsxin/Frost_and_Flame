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

#include <SDL/SDL_ttf.h>
#include <GL/gl.h>
#include <string>
#include <sstream>
#include "font.hpp"
#include "../game.hpp"

#define GL_BGR  0x80E0
#define GL_BGRA 0x80E1

extern game_class game;

font_class::font_class(void)
{

};

font_class::~font_class(void)
{
    TTF_CloseFont(font_class::font_data);
};

bool font_class::load(std::string file_name)
{
    font_class::font_data = TTF_OpenFont(file_name.c_str(), 12);
    if(font_class::font_data == NULL) game.core.log.file_write("Error loading font -> ", file_name);
    return(true);
};

bool font_class::load(std::string file_name, int pt_size)
{
    font_class::font_data = TTF_OpenFont(file_name.c_str(), pt_size);
    if(font_class::font_data == NULL) game.core.log.file_write("Error loading font -> ", file_name);
    return(true);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,std::string text,int int_data)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint texture_data;
        GLenum texture_format;
        GLint  nOfColors;
        float  width;
        float  height;
        const char *write_data;
        std::stringstream temp_string;
        temp_string << int_data;
        text = text + temp_string.str();
        write_data = text.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x ) -1);
        height = ((font_string->h / game.core.config.display_resolution_y ) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        width  = width  / 8.0f;
        height = height / 16.0f;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,std::string text,float float_data)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint texture_data;
        GLenum texture_format;
        GLint  nOfColors;
        float  width;
        float  height;
        const char *write_data;
        std::stringstream temp_string;
        temp_string << float_data;
        text = text + temp_string.str();
        write_data = text.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x ) -1);
        height = ((font_string->h / game.core.config.display_resolution_y ) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        width  = width  / 8.0f;
        height = height / 16.0f;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,std::string text)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint texture_data;
        GLenum texture_format;
        GLint  nOfColors;
        float  width;
        float  height;
        const char *write_data = text.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        width  = width  / 8.0f;
        height = height / 16.0f;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,std::string text)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint texture_data;
        GLenum texture_format;
        GLint  nOfColors;
        float  width;
        float  height;
        const  char* write_data = text.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};



bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,std::string text,int int_data)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data( text.begin(), text.end() );
        std::stringstream temp_string;
        temp_string << int_data;
        string_data += temp_string.str();
        write_data = string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,std::string text,float float_data)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data( text.begin(), text.end() );
        std::stringstream temp_string;
        temp_string << float_data;
        string_data += temp_string.str();
        write_data = string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,std::string text,int int_data,std::string text_2)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data( text.begin(), text.end() );
        std::stringstream temp_string;
        temp_string << int_data;
        string_data += temp_string.str();
        string_data += text_2;
        write_data = string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,std::string text,float float_data,std::string text_2)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data( text.begin(), text.end() );
        std::stringstream temp_string;
        temp_string << float_data;
        string_data += temp_string.str();
        string_data += text_2;
        write_data  = string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,float float_data,std::string text)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data_2( text.begin(), text.end() );
        std::string string_data;
        std::stringstream temp_string;
        temp_string << float_data;
        string_data += temp_string.str();
        string_data += string_data_2;
        write_data = string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,unsigned long long ullint_data,std::string text)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data_2( text.begin(), text.end() );
        std::string string_data;
        std::stringstream temp_string;
        temp_string << ullint_data;
        string_data += temp_string.str();
        string_data += string_data_2;
        write_data = string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,int int_data,std::string text)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data_2( text.begin(), text.end() );
        std::string string_data;
        std::stringstream temp_string;
        temp_string << int_data;
        string_data += temp_string.str();
        string_data += string_data_2;
        write_data = string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,std::string text_data,std::string text)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data( text_data.begin(), text_data.end() );
        string_data += text;
        write_data  = string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,std::string text,unsigned long long ullint_data)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data( text.begin(), text.end() );
        std::stringstream temp_string;
        temp_string << ullint_data;
        string_data += temp_string.str();
        write_data = string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,std::string text,unsigned long long ullint_data,std::string text_2)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data( text.begin(), text.end() );
        std::stringstream temp_string;
        temp_string << ullint_data;
        string_data += temp_string.str();
        string_data += text_2;
        write_data = string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};

bool font_class::write(Uint8 r,Uint8 g,Uint8 b,Uint8 a,float x,float y,float ws,float hs,std::string text,int int_data,std::string text_2,int int_data_2,std::string text_3)
{
    if ((text.length() > 0) && (font_class::font_data != NULL))
    {
        GLuint             texture_data;
        GLenum             texture_format;
        GLint              nOfColors;
        float              width;
        float              height;
        const char *write_data;
        std::string string_data( text.begin(), text.end() );
        std::stringstream temp_string;
        std::stringstream temp_string_2;
        temp_string   << int_data;
        string_data   += temp_string.str();
        string_data   += text_2;
        temp_string_2 << int_data_2;
        string_data   += temp_string_2.str();
        string_data   += text_3;
        write_data    =  string_data.c_str();
        SDL_Color font_color = {b,g,r,a};
        SDL_Surface *font_string = TTF_RenderUTF8_Blended(font_class::font_data,write_data,font_color);
        width  = ((font_string->w / game.core.config.display_resolution_x) -1);
        height = ((font_string->h / game.core.config.display_resolution_y) -1);
        if(width  < 0)  width  *= -1;
        if(height < 0)  height *= -1;
        if (ws == 0) ws = width;
        if (hs == 0) hs = height;
        width  = width  / ws;
        height = height / hs;
        nOfColors = font_string->format->BytesPerPixel;
        texture_format = GL_RGBA;
        glPushMatrix();
        glGenTextures( 1, &texture_data);
        glBindTexture( GL_TEXTURE_2D, texture_data);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexImage2D( GL_TEXTURE_2D, 0, nOfColors, font_string->w, font_string->h, 0, texture_format, GL_UNSIGNED_BYTE, font_string->pixels );
        glBindTexture(GL_TEXTURE_2D, texture_data);
        glLoadIdentity();
        glBegin( GL_QUADS );
        glTexCoord2i( 1, 0 );glVertex3f(x+width,y+height, 0.1f );
        glTexCoord2i( 1, 1 );glVertex3f(x+width,y       , 0.1f );
        glTexCoord2i( 0, 1 );glVertex3f(x      ,y       , 0.1f );
        glTexCoord2i( 0, 0 );glVertex3f(x      ,y+height, 0.1f );
        glEnd();
        glPopMatrix();
        glDeleteTextures(1, &texture_data);
        SDL_FreeSurface(font_string);
        return(true);
    }
    else return(false);
};


