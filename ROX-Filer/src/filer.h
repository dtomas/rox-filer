/*
 * $Id$
 *
 * ROX-Filer, filer for the ROX desktop project
 * By Thomas Leonard, <tal197@ecs.soton.ac.uk>.
 */

#ifndef _FILER_H
#define _FILER_H

#include <gtk/gtk.h>
#include "collection.h"
#include "pixmaps.h"
#include <sys/types.h>
#include <dirent.h>

typedef struct _FilerWindow FilerWindow;
typedef enum {PANEL_NO, PANEL_TOP, PANEL_BOTTOM} PanelType;

typedef enum
{
	OPEN_SHIFT		= 0x01,	/* Do ShiftOpen */
	OPEN_SAME_WINDOW	= 0x02, /* Directories open in same window */
	OPEN_CLOSE_WINDOW	= 0x04, /* Opening files closes the window */
	OPEN_FROM_MINI		= 0x08,	/* Non-dir => close minibuffer */
} OpenFlags;

typedef enum
{
	FILER_NEEDS_RESCAN	= 0x01, /* Call may_rescan after scanning */
	FILER_UPDATING		= 0x02, /* (scanning) items may already exist */
} FilerFlags;

#include "mount.h"
#include "minibuffer.h"
#include "dir.h"
#include "type.h"
#include "display.h"

struct _FilerWindow
{
	GtkWidget	*window;
	gboolean	scanning;	/* State of the 'scanning' indicator */
	guchar		*path;		/* pathname */
	Collection	*collection;
	gboolean	temp_item_selected;
	gboolean	show_hidden;
	FilerFlags	flags;
	PanelType	panel_type;
	int 		(*sort_fn)(const void *a, const void *b);

	DetailsType	details_type;
	DisplayStyle	display_style;

	Directory	*directory;

	gboolean	had_cursor;	/* (before changing directory) */
	char		*auto_select;	/* If it we find while scanning */

	GtkWidget	*minibuffer_area;	/* The hbox to show/hide */
	GtkWidget	*minibuffer_label;	/* The operation name */
	GtkWidget	*minibuffer;		/* The text entry */
	int		mini_cursor_base;
	MiniType	mini_type;

	/* TRUE if hidden files are shown because the minibuffer leafname
	 * starts with a dot.
	 */
	gboolean 	temp_show_hidden;
};

extern FilerWindow 	*window_with_focus;
extern GList		*all_filer_windows;
extern GHashTable	*child_to_filer;
extern gboolean 	o_unique_filer_windows;
extern gboolean		o_single_click;
extern gboolean 	o_new_window_on_1;

/* Prototypes */
void filer_init(void);
FilerWindow *filer_opendir(char *path, PanelType panel_type);
void filer_update_dir(FilerWindow *filer_window, gboolean warning);
int selected_item_number(Collection *collection);
DirItem *selected_item(Collection *collection);
void change_to_parent(FilerWindow *filer_window);
void full_refresh(void);
void filer_openitem(FilerWindow *filer_window, int item_number,
		OpenFlags flags);
void filer_check_mounted(char *path);
void filer_change_to(FilerWindow *filer_window, char *path, char *from);
gboolean filer_exists(FilerWindow *filer_window);
void filer_open_parent(FilerWindow *filer_window);
void filer_detach_rescan(FilerWindow *filer_window);

#endif /* _FILER_H */
