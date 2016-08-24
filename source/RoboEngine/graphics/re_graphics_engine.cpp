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

#include "re_graphics_engine.hpp"

namespace RoboEngine
{

    uint32_t re_cGraphicsEngine::initialize(void)
    {
        uint32_t return_value = EXIT_SUCCESS;
        glfwWindowHint(GLFW_SAMPLES, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, RE_GL_CONTEXT_MAJOR);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, RE_GL_CONTEXT_MINOR);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        m_currentDisplay = 0;
        m_currentDisplayMode = 0;
        // todo: create list of available display modes, if full screen flag, set to optimal full screen resolution.

        m_window = glfwCreateWindow( m_displayX, m_displayY, m_title.c_str(), nullptr, nullptr);
        if (m_window == nullptr)
        {
            RoboEngine::log_write(ROBOENGINELOG, __FILE__, __FUNCTION__, __LINE__, "Non fatal warning - Unable to create a window.");
            glfwTerminate();
            return_value = EXIT_FAILURE;
        }
        else
        {
            glfwMakeContextCurrent(m_window);
            glewExperimental = true;
            glfwSwapInterval(1);
            if (glewInit() != GLEW_OK)
            {
                RoboEngine::log_write(ROBOENGINELOG, __FILE__, __FUNCTION__, __LINE__, "Fatal error - Unable to initialize GLEW.");
                glfwTerminate();
                return_value = EXIT_FAILURE;
            }
            else
            {
                RoboEngine::log_write(ROBOENGINELOG, __FILE__, __FUNCTION__, __LINE__, reinterpret_cast<const char*>(glGetString(GL_VERSION)));
                RoboEngine::log_write(ROBOENGINELOG, __FILE__, __FUNCTION__, __LINE__, reinterpret_cast<const char*>(glGetString(GL_VENDOR)));
                RoboEngine::log_write(ROBOENGINELOG, __FILE__, __FUNCTION__, __LINE__, reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
                RoboEngine::log_write(ROBOENGINELOG, __FILE__, __FUNCTION__, __LINE__, reinterpret_cast<const char*>(glGetString(GL_SHADING_LANGUAGE_VERSION)));


                glClearColor(0.1f,0.1f,0.4f,1);
                glClearDepth(1.0);

            }
        }
        return return_value;
    }

    void re_cGraphicsEngine::deinitialize(void)
    {
        glfwDestroyWindow(m_window);
    }

    void re_cGraphicsEngine::render(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_entity = m_entityHead;
        if (m_entity != nullptr)
        {
            while (m_entity  != nullptr)
            {
                if ((m_entity->enabled) && (m_entity->render != nullptr))
                {
                    //shader
                    if ((m_entity->render->shader != nullptr) && (m_entity->render->shader->ID != 0) && (m_currentShader != m_entity->render->shader->ID))
                    {
                        if (m_currentShader != m_entity->render->shader->ID)
                        {
                            glUseProgram(0);
                            for (uint16_t i = 0; i < m_entity->render->shader->numAttributes; i++)
                                glDisableVertexAttribArray(i);
                            m_currentShader = 0;
                        }
                        if (m_currentShader == 0)
                        {
                            m_currentShader = m_entity->render->shader->ID;
                            glUseProgram(m_entity->render->shader->ID);
                            for (uint16_t i = 0; i < m_entity->render->shader->numAttributes; i++)
                                glEnableVertexAttribArray(i);
                        }
                        // initialize mesh
                        if (m_entity->render->shader->ID == 0)
                        {
                            glGenBuffers(1, &m_entity->render->shader->ID);
                            glBindBuffer(GL_ARRAY_BUFFER, m_entity->render->shader->ID);
                            glBufferData(GL_ARRAY_BUFFER, sizeof(m_entity->render->mesh->index), m_entity->render->mesh->index, GL_STATIC_DRAW);
                            glBindBuffer(GL_ARRAY_BUFFER, 0);
                        }
                        // render mesh
                        if (m_entity->render->shader->ID != 0)
                        {
                            glBindBuffer(GL_ARRAY_BUFFER, m_entity->render->shader->ID);
                            glEnableVertexAttribArray(0);

                            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(v8_f), (void*)offsetof(v8_f, x));
                            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(v8_f), (void*)offsetof(v8_f, nx));
                            glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(v8_f), (void*)offsetof(v8_f, s));

                            glDrawArrays(GL_TRIANGLES, 0, (m_entity->render->mesh->indexCount/3));

                            glEnableVertexAttribArray(0);
                            glBindBuffer(GL_ARRAY_BUFFER, 0);
                        }
                    }

                }
                m_entity = m_entity->next;
            }
        }
        glfwSwapBuffers(m_window);
    }

}

