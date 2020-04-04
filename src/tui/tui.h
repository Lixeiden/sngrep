/**************************************************************************
 **
 ** sngrep - SIP Messages flow viewer
 **
 ** Copyright (C) 2013-2019 Ivan Alonso (Kaian)
 ** Copyright (C) 2013-2019 Irontec SL. All rights reserved.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU General Public License as published by
 ** the Free Software Foundation, either version 3 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU General Public License for more details.
 **
 ** You should have received a copy of the GNU General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **
 ****************************************************************************/
/**
 * @file manager.h
 * @author Ivan Alonso [aka Kaian] <kaian@irontec.com>
 *
 * @brief Functions to manage interface panels
 *
 * All sngrep panel pointers are encapsulated into a ui structure that is
 * used to invoke custom functions for creating, destroying, drawing, etc
 * the screens.
 *
 * This structure also manages concurrent updates and access to ncurses
 * panel pointers.
 *
 */
#ifndef __SNGREP_UI_MANAGER_H
#define __SNGREP_UI_MANAGER_H

#include "config.h"
#include <ncurses.h>
#include <panel.h>
#include "tui/theme.h"
#include "tui/keybinding.h"
#include "storage/storage.h"
#include "storage/group.h"
#include "tui/widgets/box.h"
#include "tui/widgets/container.h"
#include "tui/widgets/entry.h"
#include "tui/widgets/label.h"
#include "tui/widgets/menu.h"
#include "tui/widgets/menu_bar.h"
#include "tui/widgets/menu_item.h"
#include "tui/widgets/scrollbar.h"
#include "tui/widgets/widget.h"
#include "tui/widgets/window.h"
#include "setting.h"

//! Error reporting
#define TUI_ERROR (capture_pcap_error_quark())

//! Error codes
enum tui_errors
{
    TUI_ERROR_INIT = 0,
};

typedef enum
{
    SETTING_BACKGROUND_DARK,
    SETTING_BACKGROUND_DEFAULT,
} SettingBackground;

typedef enum
{
    SETTING_COLORMODE_REQUEST,
    SETTING_COLORMODE_CSEQ,
    SETTING_COLORMODE_CALLID,
} SettingColorMode;

/**
 * @brief Get TUI omain struct for GError
 */
GQuark
tui_error_quark();

/**
 * @brief Initialize ncurses mode
 *
 * @param error GError with failure description (optional)
 * @return TRUE on initialization success, FALSE otherwise
 */
gboolean
tui_init(GMainLoop *loop, GError **error);

/**
 * @brief Stops ncurses mode
 *
 * This functions will deinitialize ncurses mode
 *
 * @returns 0 on ncurses initialization success, 1 otherwise
 */
void
tui_deinit();

/**
 * @brief Determine if ncurses mode has been enabled
 * @return TRUE if ncurses screens has been initialized, FALSE otherwise
 */
gboolean
tui_is_enabled();

/**
 * @brief Create a panel of a given type
 *
 * Create a ncurses panel of the given type.
 * This function is a small wrapper for panel create function
 *
 * @param type Panel Type
 * @return the ui structure with the panel pointer created*
 */
Window *
tui_create_window(WindowType type);

/**
 * @brief Find a ui from its panel pointer
 */
Window *
tui_find_by_panel(PANEL *panel);

/**
 * @brief Find a ui form its panel id
 */
Window *
tui_find_by_type(WindowType type);

/**
 * @brief Default handler for keys
 *
 * If ui doesn't handle the given key (ui_handle_key returns the key value)
 * then the default handler will be invoked
 *
 * @param window Current displayed UI structure
 * @param key key pressed by user
 */
int
tui_default_keyhandler(Window *window, int key);

/**
 * @brief Call Resize function in all panels in the stack
 *
 * This function acts as handler of screen resize function invoking all
 * resize functions of panels that implement it.
 */
void
tui_resize_panels();

/**
 * @brief Draw a box around passed windows
 *
 * Draw a box around passed windows  with two bars
 * (top and bottom) of one line each.
 *
 * @param win Window to draw borders on
 */
void
title_foot_box(PANEL *panel);

/**
 * @brief Draw a message payload in a window
 *
 * Generic drawing function for payload. This function will start
 * writing at 0,0 and return the number of lines written.
 *
 * @param win Ncurses window to draw payload
 * @param msg Msg to be drawn
 */
int
draw_message(WINDOW *win, Message *msg);

/**
 * @brief Draw a message payload in a window starting at a given line
 *
 * Generic drawing function for payload. This function will start
 * writing at line starting and first column and return the number
 * of lines written.
 *
 * @param win Ncurses window to draw payload
 * @param msg Msg to be drawn
 * @param starting Number of win line to start writing payload
 */
int
draw_message_pos(WINDOW *win, Message *msg, int starting);

/**
 * @brief Return UTF-8 representation for a given character
 * @param acs Ncurses ASC character
 * @return a static pointer to a wchar string
 */
wchar_t *
tui_acs_utf8(chtype acs);

#endif    // __SNGREP_UI_MANAGER_H
