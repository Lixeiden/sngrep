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
 * @file keybinding.h
 * @author Ivan Alonso [aka Kaian] <kaian@irontec.com>
 *
 * @brief Functions to manage keybindings
 *
 * sngrep keybindings are associated with actions. Each action can store multiple
 * keybindings.
 * Keybindings configured by user using *key* directive of sngreprc file,
 * in the format:
 *
 *   key ui_action keycode
 *
 * keycode must be a letter (lowercase or uppercase) or a ^ sign with an uppercase
 * letter when Ctrl modifier is used.
 *
 */

#ifndef __SNGREP_KEYBINDING_H_
#define __SNGREP_KEYBINDING_H_

#include <glib.h>

//! Number of keybindings per action
#define MAX_BINDINGS    5

//! Some undefined key codes
#define KEY_CTRL(n)     ((n)-64)
#define KEY_ESC         27
#define KEY_INTRO       10
#define KEY_TAB         9
#define KEY_SHTAB       353
#define KEY_BACKSPACE2  8
#define KEY_BACKSPACE3  127
#define KEY_SPACE       ' '

/**
 * @brief Available Key actions
 */
typedef enum
{
    ACTION_UNKNOWN = -1,
    ACTION_PRINTABLE = 0,
    ACTION_UP,
    ACTION_DOWN,
    ACTION_LEFT,
    ACTION_RIGHT,
    ACTION_DELETE,
    ACTION_BACKSPACE,
    ACTION_NPAGE,
    ACTION_PPAGE,
    ACTION_HNPAGE,
    ACTION_HPPAGE,
    ACTION_BEGIN,
    ACTION_END,
    ACTION_PREV_FIELD,
    ACTION_NEXT_FIELD,
    ACTION_RESIZE_SCREEN,
    ACTION_CLEAR,
    ACTION_CLEAR_CALLS,
    ACTION_CLEAR_CALLS_SOFT,
    ACTION_TOGGLE_SYNTAX,
    ACTION_CYCLE_COLOR,
    ACTION_COMPRESS,
    ACTION_SHOW_ALIAS,
    ACTION_TOGGLE_PAUSE,
    ACTION_PREV_SCREEN,
    ACTION_SHOW_HELP,
    ACTION_SHOW_RAW,
    ACTION_SHOW_FLOW,
    ACTION_SHOW_FLOW_EX,
    ACTION_SHOW_FILTERS,
    ACTION_SHOW_COLUMNS,
    ACTION_SHOW_SETTINGS,
    ACTION_SHOW_STATS,
    ACTION_SHOW_PLAYER,
    ACTION_SHOW_PROTOCOLS,
    ACTION_COLUMN_MOVE_UP,
    ACTION_COLUMN_MOVE_DOWN,
    ACTION_SDP_INFO,
    ACTION_HIDE_DUPLICATE,
    ACTION_DISP_FILTER,
    ACTION_SAVE,
    ACTION_AUTH_VALIDATE,
    ACTION_SELECT,
    ACTION_CONFIRM,
    ACTION_TOGGLE_MEDIA,
    ACTION_ONLY_MEDIA,
    ACTION_TOGGLE_RAW,
    ACTION_INCREASE_RAW,
    ACTION_DECREASE_RAW,
    ACTION_RESET_RAW,
    ACTION_ONLY_SDP,
    ACTION_TOGGLE_HINT,
    ACTION_AUTOSCROLL,
    ACTION_SORT_PREV,
    ACTION_SORT_NEXT,
    ACTION_SORT_SWAP,
    ACTION_TOGGLE_TIME,
    ACTION_SENTINEL
}  KeybindingAction;

//! Shorter declaration of key_binding structure
typedef struct _Keybinding Keybinding;

/**
 * @brief Struct to hold a keybinding data
 */
struct _Keybinding
{
    //! Keybinding action id
    KeybindingAction id;
    //! Keybinding action name
    const gchar *name;
    //! keybindings for this action
    gint keys[MAX_BINDINGS];
    //! How many keys are binded to this action
    guint bindcnt;
};

/**
 * @brief Print configured keybindigs
 */
void
key_bindings_dump();

/**
 * @brief Bind a key to an action
 *
 * @param action One action defined in @KeybindingAction
 * @param key Keycode returned by getch
 */
void
key_bind_action(KeybindingAction action, gint key);

/**
 * @brief Unbind a key to an action
 *
 * @param action One action defined in @KeybindingAction
 * @param key Keycode returned by getch
 */
void
key_unbind_action(KeybindingAction action, gint key);

/**
 * @brief Find the next action for a given key
 *
 * Set start parameter to -1 for start searching the
 * first action.
 *
 * @param key Keycode returned by getch
 */
KeybindingAction
key_find_action(gint key, KeybindingAction start);

/**
 * @brief Return the action id associate to an action str
 *
 * This function is used to translate keybindings configuration
 * found in sngreprc file to internal Action IDs
 *
 * @param action Configuration string for an action
 * @return action id from @KeybindingAction (may be ACTION_UNKNOWN)
 */
KeybindingAction
key_action_id(const gchar *action);

/**
 * @brief Parse Human key declaration to curses key
 *
 * This function is used to translate keybindings configuration
 * keys found in sngreprc file into internal ncurses keycodes
 *
 * @return ncurses keycode for the given key string
 */
gint
key_from_str(const gchar *key);

/**
 * @brief Return Human readable key for an action
 *
 * This function is used to display keybindings in the bottom bar
 * of panels. Depending on sngrep configuration it will display the
 * first associated keybding with the action or the second one
 * (aka alternative).
 *
 * @param action One action defined in @KeybindingAction
 * @return Main/Alt keybinding for the given action
 */
const gchar *
key_action_key_str(KeybindingAction action);

#endif /* __SNGREP_KEYBINDING_H_ */
