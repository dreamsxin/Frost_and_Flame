/**
 * Copyright (C) Paul Wortmann, PhysHex Games, www.physhexgames.com
 * This file is part of "Frost And Flame"
 *
 * "Frost And Flame" is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 2 only.
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
 * @website www.physhexgames.com
 * @license GPL V2
 * @date 2011-11-11
 */

#include "re_system_events.hpp"
#include "../roboengine.hpp"

namespace RoboEngine
{

    void re_cSystemEvents::initialize(GLFWwindow* _window)
    {
        m_window = _window;
        if (_window == nullptr)
            re_logWrite("Fatal error - Failed to initialize system event manager", RE_ENGINE_LOG, __FILE__, __LINE__, __FUNCTION__);
        else
            glfwSetInputMode(m_window, GLFW_STICKY_KEYS, GL_TRUE);
    }

    void re_cSystemEvents::terminate(void)
    {
    }

    void re_cSystemEvents::process(void)
    {
        if (glfwWindowShouldClose(m_window) == GL_TRUE)
            m_quit = true;
    }

}

