/*
*****************************************************************
                          COPYRIGHT NOTIFICATION
*****************************************************************

THE FOLLOWING IS A NOTICE OF COPYRIGHT, AVAILABILITY OF THE CODE,
AND DISCLAIMER WHICH MUST BE INCLUDED IN THE PROLOGUE OF THE CODE
AND IN ALL SOURCE LISTINGS OF THE CODE.

(C)  COPYRIGHT 1993 UNIVERSITY OF CHICAGO

Argonne National Laboratory (ANL), with facilities in the States of
Illinois and Idaho, is owned by the United States Government, and
operated by the University of Chicago under provision of a contract
with the Department of Energy.

Portions of this material resulted from work developed under a U.S.
Government contract and are subject to the following license:  For
a period of five years from March 30, 1993, the Government is
granted for itself and others acting on its behalf a paid-up,
nonexclusive, irrevocable worldwide license in this computer
software to reproduce, prepare derivative works, and perform
publicly and display publicly.  With the approval of DOE, this
period may be renewed for two additional five year periods.
Following the expiration of this period or periods, the Government
is granted for itself and others acting on its behalf, a paid-up,
nonexclusive, irrevocable worldwide license in this computer
software to reproduce, prepare derivative works, distribute copies
to the public, perform publicly and display publicly, and to permit
others to do so.

*****************************************************************
                                DISCLAIMER
*****************************************************************

NEITHER THE UNITED STATES GOVERNMENT NOR ANY AGENCY THEREOF, NOR
THE UNIVERSITY OF CHICAGO, NOR ANY OF THEIR EMPLOYEES OR OFFICERS,
MAKES ANY WARRANTY, EXPRESS OR IMPLIED, OR ASSUMES ANY LEGAL
LIABILITY OR RESPONSIBILITY FOR THE ACCURACY, COMPLETENESS, OR
USEFULNESS OF ANY INFORMATION, APPARATUS, PRODUCT, OR PROCESS
DISCLOSED, OR REPRESENTS THAT ITS USE WOULD NOT INFRINGE PRIVATELY
OWNED RIGHTS.

*****************************************************************
LICENSING INQUIRIES MAY BE DIRECTED TO THE INDUSTRIAL TECHNOLOGY
DEVELOPMENT CENTER AT ARGONNE NATIONAL LABORATORY (630-252-2000).
*/
/*****************************************************************************
 *
 *     Original Author : Mark Anderson
 *     Second Author   : Frederick Vong
 *     Third Author    : Kenneth Evans, Jr.
 *
 *****************************************************************************
*/

/*
 * include file for widget-based display manager
 */
#ifndef __MEDMWIDGET_H__
#define __MEDMWIDGET_H__


#ifdef ALLOCATE_STORAGE
#define EXTERN
#else
#define EXTERN extern
#endif

#include <limits.h>
#include <sys/types.h>
#if 0
#include <sys/times.h>
#else
#include <time.h>
#endif
#include "xtParams.h"


#include "displayList.h"


/* this is ugly, but we need it for the action table */
#if 0
extern void popupValuatorKeyboardEntry(Widget, XEvent*, String *, Cardinal *);
#endif

#ifndef MAX
#define MAX(a,b)  ((a)>(b)?(a):(b))
#endif
#ifndef MIN
#define MIN(a,b)  ((a)<(b)?(a):(b))
#endif

#ifndef STRDUP
#define STRDUP(a) (strcpy( (char *)malloc(strlen(a)+1),a))
#endif

/* file suffix definitions (as dir/file masks for file selection boxes) */
#define DISPLAY_DIALOG_MASK	"*.adl"	/* ascii display files */
#define RESOURCE_DIALOG_MASK	"*.rsc"	/* resource files */
#define COLOR_DIALOG_MASK	"*.clr"	/* colormap/color editor files */
#define CHANNEL_DIALOG_MASK	"*.chn"	/* channel list files */

#define DISPLAY_LIST_ENV "EPICS_DISPLAY_PATH"

#define DISPLAY_DIALOG_TITLE	"EPICS Display Manager"
#define DISPLAY_DIALOG_CANCEL_STRING	"Exit DM"
#define DISPLAY_FILE_BACKUP_SUFFIX	"_BAK"
#define DISPLAY_FILE_ASCII_SUFFIX	".adl"
#define DISPLAY_FILE_BINARY_SUFFIX	".dl"
#define DISPLAY_XWD_FILE		"/tmp/medm.xwd"
#define MORE_TO_COME_SYMBOL	"..."	/* string for dialog popups        */
#define SHELL_CMD_PROMPT_CHAR	'?'	/* shell cmd. prompt indicator     */
#define DUMMY_TEXT_FIELD	"9.876543" /* dummy string for text calc.  */

#define NUM_EXECUTE_POPUP_ENTRIES	2	/* items in exec. popup menu */
#define EXECUTE_POPUP_MENU_PRINT	"Print" /* if this changes, change    */
#define EXECUTE_POPUP_MENU_CLOSE	"Close" /* executePopupMenuCallback() */
#define EXECUTE_POPUP_MENU_PRINT_ID	0
#define EXECUTE_POPUP_MENU_CLOSE_ID	1

#define COLOR_SCALE		(65535.0/255.0)
#define MAX_CHILDREN		1000	/* max # of child widgets...       */
#define MAX_TEXT_UPDATE_WIDTH	64	/* max length of text update       */
#define BORDER_WIDTH		5	/* border for valuator (for MB2)   */

/* for argument passing in related displays */
#define RELATED_DISPLAY_FILENAME_INDEX 0
#define RELATED_DISPLAY_ARGS_INDEX 1
#define RELATED_DISPLAY_FILENAME_AND_ARGS_SIZE	(RELATED_DISPLAY_ARGS_INDEX+1)

/* display object or widget specific parameters */
#define METER_OKAY_SIZE		80	/* (meter>80) ? 11 : 5 markers     */
#define METER_MARKER_DIVISOR	9	/* height/9 = marker length        */
#define METER_FONT_DIVISOR	8	/* height/8 = height of font       */
#define METER_VALUE_FONT_DIVISOR 10	/* height/10 = height of value font*/
#define INDICATOR_MARKER_WIDTH	4	/* good "average" width            */
#define INDICATOR_MARKER_DIVISOR 20	/* height/20 = marker length (pair)*/
#define INDICATOR_OKAY_SIZE	80	/* (meter>80) ? 11 : 5 markers     */
#define INDICATOR_FONT_DIVISOR	8	/* height/8 = height of font       */
#define INDICATOR_VALUE_FONT_DIVISOR 10	/* height/10 = height of value font*/
#define GOOD_MARGIN_DIVISOR	10	/* height/10 = marginHeight/Width  */
#define BAR_TOO_SMALL_SIZE	30	/* bar is too small for extra data */

#define STRIP_NSAMPLES		60	/* number of samples to save       */

#define SECS_PER_MIN		60.0
#define SECS_PER_HOUR		(60.0 * SECS_PER_MIN)
#define SECS_PER_DAY		(24.0 * SECS_PER_HOUR)

/* default display name, widths, heights for newly created displays */
#define DEFAULT_FILE_NAME	"newDisplay.adl"
#define DEFAULT_DISPLAY_WIDTH	400
#define DEFAULT_DISPLAY_HEIGHT	400

/* highlight line thickness */
#define HIGHLIGHT_LINE_THICKNESS 2

/* valuator-specific parameters */
#define VALUATOR_MIN		0
#define VALUATOR_MAX 		1000000
#define VALUATOR_INCREMENT 	1
#define VALUATOR_MULTIPLE_INCREMENT 2

/*
 * specific fonts being used (intended to be aliased to best fitting font)
 */
#define MAX_FONTS		16		/* max # of fonts             */
#define LAST_CHANCE_FONT	"fixed"		/* a common font              */
#define ALIAS_FONT_PREFIX	"widgetDM_"	/* append pixel sz. for alias */

#define FONT_ALIASES_STRING	"alias"
#define DEFAULT_SCALABLE_STRING	"scalable"

/* Speedo scalable, available from  X11R5 font server */
#define DEFAULT_SCALABLE_DISPLAY_FONT \
"-bitstream-charter-bold-r-normal--0-0-0-0-p-0-iso8859-1"


#ifndef ALLOCATE_STORAGE
extern int fontSizeTable[MAX_FONTS];
#else
int fontSizeTable[MAX_FONTS] = {4,6,8,10,12,14,16,18,20,
				22,24,30,36,40,48,60,};
#endif


/*
 * add in action table for complicated actions
 */
#if 0
static XtActionsRec actions[] = {
    {"popupValuatorKeyboardEntry",popupValuatorKeyboardEntry},
};
#endif

/************************************************************************
 * special types
 ************************************************************************/

/*
 * shell types that mdm/medd must worry about
 */
typedef enum {DISPLAY_SHELL, OTHER_SHELL} ShellType;

/*
 * action types for MB in display (based on object palette state
 */
typedef enum {SELECT_ACTION, CREATE_ACTION} ActionType;

/*
 *  update tasks
 */

typedef struct _UpdateTask {
    void       (*executeTask)(XtPointer);    /* update rountine */
    void       (*destroyTask)(XtPointer);
    Widget     (*widget)(XtPointer);
    void       (*name)(XtPointer, char **, short *, int *);
    XtPointer  clientData;                           
    double     timeInterval;                 /* if not 0.0, periodic task */
    double     nextExecuteTime;               
    struct     _DisplayInfo *displayInfo;
    struct     _UpdateTask *next;
    int        executeRequestsPendingCount;  /* how many update requests are pending */
    XRectangle rectangle;                    /* geometry of the Object */
    Boolean    overlapped;                   /* tell whether this object is overlapped
					      * by other objects */
    Boolean    opaque;
} UpdateTask;

typedef struct _InitTask {
    Boolean init;
    Boolean (*initTask)();
} InitTask;

/*
 * name-value table (for macro substitutions in display files)
 */
typedef struct {
    char *name;
    char *value;
} NameValueTable;


/* 
 * EPICS Display specific information: one per display file
 */

typedef struct _DisplayInfo {
    FILE		  *filePtr;
    Boolean   newDisplay;
    int       versionNumber;
  /* widgets and main pixmap */
    Widget    shell;
    Widget    drawingArea;
    Pixmap    drawingAreaPixmap;
    Widget    editPopupMenu;
    Widget    executePopupMenu;
    Widget    cartesianPlotPopupMenu;
    Widget    selectedCartesianPlot;
    Widget    warningDialog;
    int       warningDialogAnswer;
    Widget    questionDialog;
    int       questionDialogAnswer;
    Widget    shellCommandPromptD;
  /* widget instance data */
#if 0
    Widget		child[MAX_CHILDREN];	  /* children of drawing area */
    int		    childCount;
#endif
  /* periodic tasks */
    UpdateTask      updateTaskListHead;
    UpdateTask      *updateTaskListTail;
    int             periodicTaskCount;
  /* colormap and attribute data (one exists at a time for each display)        */
    Pixel *colormap;
    int		dlColormapCounter;
    int		dlColormapSize;
    int		drawingAreaBackgroundColor;
    int		drawingAreaForegroundColor;
    GC		gc;
    GC		pixmapGC;
  /* execute or edit mode traversal  */
    DlTraversalMode	traversalMode;
    Boolean		hasBeenEditedButNotSaved;
    Boolean		fromRelatedDisplayExecution;
  /* display list pointers */
    DlList *dlElementList;

  /* for edit purposes */
    DlList *selectedDlElementList;
    Boolean selectedElementsAreHighlighted;

  /* for macro-substitution in display lists */
    NameValueTable	*nameValueTable;
    int		 numNameValues;

    DlFile *dlFile;
    DlColormap *dlColormap;

  /* linked list of displayInfo's    */
    struct _DisplayInfo *next;
    struct _DisplayInfo *prev;

} DisplayInfo;



/*
 * miscellaneous support structures
 */
typedef struct {
    XtPointer	controllerData;	/* (ChannelAccessControllerData *) */
    int		nButtons;
    XmButtonType	*buttonType;
    XmStringTable	buttons;
} OptionMenuData;			/* used for MENU type */


/***
 *** ELEMENT_STRING_TABLE for definition of strings for display elements
 ***	any changes of types or ordering of {DL_Valuator,...,DL_Meter,...} etc
 ***	in displayList.h must have corresponding changes in this table!!
 ***/
#ifndef ALLOCATE_STORAGE
extern char *elementStringTable[NUM_DL_ELEMENT_TYPES];
extern XmString elementXmStringTable[NUM_DL_ELEMENT_TYPES];
#else
char *elementStringTable[NUM_DL_ELEMENT_TYPES] = {
    "Element","Composite", "Display",
    "Choice Button", "Menu", "Message Button", "Related Display",
    "Shell Command", "Text Entry", "Valuator",
    "Bar", "Byte", "Cartesian Plot", "Indicator", "Meter",
    "Strip Chart", "Text Update",
    "Arc", "Image", "Line", "Oval", "Polygon", "Polyline", "Rectangle", "Text"
};
XmString elementXmStringTable[NUM_DL_ELEMENT_TYPES];
#endif

/****************************************************************************
 ****				Resource Bundle type			 ****
 ***
 ***  this gets tricky - this is the aggregate set of all "attributes"
 ***	or resources for any object in mdm/medd.  there is some intersection
 ***	between objects (e.g., sharing DlObject) but any object ought to
 ***	be able to retrieve its necessary resources from this structure
 ***	somewhere.  look at   displayList.h   for definition of these
 ***	structure components... 
 ***	NOTE:  exceptions: Display and Colormap not in here (these are
 ***	modified by other, more user-friendly, methods)
 ****************************************************************************/

/*
 * Resource bundle type
 */
typedef struct _ResourceBundle {

  /* the aggregate types have been decomposed into scalar/atomic types to
     support the set intersection necessary */
    Position		x;
    Position		y;
    Dimension		width;
    Dimension		height;
    char			title[MAX_TOKEN_LENGTH];
    char			xlabel[MAX_TOKEN_LENGTH];
    char			ylabel[MAX_TOKEN_LENGTH];
    int			clr;
    int			bclr;
    int			begin;
    int			path;
    TextAlign		align;
    TextFormat		format;
    LabelType		label;
    Direction		direction;
    ColorMode		clrmod;
#ifdef __COLOR_RULE_H__
    int                     colorRule;
#endif
    FillMode		fillmod;
    EdgeStyle		style;
    FillStyle		fill;
    VisibilityMode		vis;
    char			chan[MAX_TOKEN_LENGTH];
    int			data_clr;
    int			dis;
    int			xyangle;
    int			zangle;
    double                  period;
    TimeUnits		units;
    CartesianPlotStyle	cStyle;
    EraseOldest		erase_oldest;
    int			count;
    Stacking		stacking;
    ImageType		imageType;
    char			textix[MAX_TOKEN_LENGTH];
    char			messageLabel[MAX_TOKEN_LENGTH];
    char			press_msg[MAX_TOKEN_LENGTH];
    char			release_msg[MAX_TOKEN_LENGTH];
    char			imageName[MAX_TOKEN_LENGTH];
    char			compositeName[MAX_TOKEN_LENGTH];
    char			data[MAX_TOKEN_LENGTH];
    char			cmap[MAX_TOKEN_LENGTH];
    char			name[MAX_TOKEN_LENGTH];
    int			lineWidth;
    double			dPrecision;
    int                     sbit, ebit;
    char      rdLabel[MAX_TOKEN_LENGTH];
    DlTrace			cpData[MAX_TRACES];
    DlPen			scData[MAX_PENS];
    DlRelatedDisplayEntry	rdData[MAX_RELATED_DISPLAYS];
    DlShellCommandEntry	cmdData[MAX_SHELL_COMMANDS];

  /* X_AXIS_ELEMENT, Y1_AXIS_ELEMENT, Y2_AXIS_ELEMENT */
    DlPlotAxisDefinition	axis[3];

    char			trigger[MAX_TOKEN_LENGTH];
    char                    erase[MAX_TOKEN_LENGTH];
    eraseMode_t             eraseMode;

  /* related display specific */
    relatedDisplayVisual_t rdVisual;

    struct _ResourceBundle	*next;	/* linked list of resourceBundle's   */
    struct _ResourceBundle	*prev;

} ResourceBundle, *ResourceBundlePtr;


/*
 * and define IDs for the resource entries for displacements into
 *   resource RC widget array
 */
#define X_RC		0
#define Y_RC		1
#define WIDTH_RC	2
#define HEIGHT_RC 	3
#define RDBK_RC		4
#define CTRL_RC		5
#define TITLE_RC	6
#define XLABEL_RC	7
#define YLABEL_RC	8

#define CLR_RC		9
#define BCLR_RC		10
#define BEGIN_RC	11
#define PATH_RC		12
#define ALIGN_RC	13
#define FORMAT_RC	14
#define LABEL_RC	15
#define DIRECTION_RC	16
#define FILLMOD_RC	17
#define STYLE_RC	18
#define FILL_RC		19
#define CLRMOD_RC	20
#ifdef __COLOR_RULE_H__
#define COLOR_RULE_RC   21              /* Color Rule Entry Table         */
#define VIS_RC          22
#define CHAN_RC         23
#define DATA_CLR_RC     24
#define DIS_RC          25
#define XYANGLE_RC      26
#define ZANGLE_RC       27
#define PERIOD_RC       28
#define UNITS_RC        29
#define CSTYLE_RC       30
#define ERASE_OLDEST_RC 31
#define COUNT_RC        32
#define STACKING_RC     33
#define IMAGETYPE_RC    34
#define TEXTIX_RC       35
#define MSG_LABEL_RC    36
#define PRESS_MSG_RC    37
#define RELEASE_MSG_RC  38
#define IMAGENAME_RC    39
#define DATA_RC         40
#define CMAP_RC         41
#define NAME_RC         42
#define LINEWIDTH_RC    43
#define PRECISION_RC    44
#define SBIT_RC         45
#define EBIT_RC         46
#define RD_LABEL_RC     47
#define RD_VISUAL_RC    48

/* vectors/matrices of data */
#define RDDATA_RC       49              /* Related Display data           */
#define CPDATA_RC       50              /* Cartesian Plot channel data    */
#define SCDATA_RC       51              /* Strip Chart data               */
#define SHELLDATA_RC    52              /* Shell Command data             */
#define CPAXIS_RC       53              /* Cartesian Plot axis data       */

/* other new entry types */
#define TRIGGER_RC      54              /* Cartesian Plot trigger channel */
#define ERASE_RC        55              /* Cartesian Plot erase channel   */
#define ERASE_MODE_RC   56              /* Cartesian Plot erase mode      */

#else
#define VIS_RC		21
#define CHAN_RC		22
#define DATA_CLR_RC	23
#define DIS_RC		24
#define XYANGLE_RC	25
#define ZANGLE_RC	26
#define PERIOD_RC	27
#define UNITS_RC	28
#define CSTYLE_RC	29
#define ERASE_OLDEST_RC	30
#define COUNT_RC	31
#define STACKING_RC	32
#define IMAGETYPE_RC	33
#define TEXTIX_RC	34
#define MSG_LABEL_RC	35
#define PRESS_MSG_RC	36
#define RELEASE_MSG_RC	37
#define IMAGENAME_RC	38
#define DATA_RC		39
#define CMAP_RC		40
#define NAME_RC		41
#define LINEWIDTH_RC	42
#define PRECISION_RC	43
#define SBIT_RC         44
#define EBIT_RC         45
#define RD_LABEL_RC     46
#define RD_VISUAL_RC    47

/* vectors/matrices of data */
#define RDDATA_RC	48		/* Related Display data		  */
#define CPDATA_RC	49		/* Cartesian Plot channel data	  */
#define SCDATA_RC	50		/* Strip Chart data		  */
#define SHELLDATA_RC	51		/* Shell Command data		  */
#define CPAXIS_RC	52		/* Cartesian Plot axis data	  */

/* other new entry types */
#define TRIGGER_RC	53		/* Cartesian Plot trigger channel */
#define ERASE_RC        54              /* Cartesian Plot erase channel   */
#define ERASE_MODE_RC   55              /* Cartesian Plot erase mode      */
#endif

#define MIN_RESOURCE_ENTRY	0
#define MAX_RESOURCE_ENTRY	(ERASE_MODE_RC + 1)

/***
 *** resourceEntryStringTable for definition of labels for resource entries
 ***	any changes of types or ordering of above must have corresponding
 ***	changes in this table!!
 ***/
#ifndef ALLOCATE_STORAGE
extern char *resourceEntryStringTable[MAX_RESOURCE_ENTRY];
#else
char *resourceEntryStringTable[MAX_RESOURCE_ENTRY] = {
    "X Position", "Y Position", "Width", "Height",
    "Readback Channel", "Control Channel",
    "Title", "X Label", "Y Label",
    "Foreground", "Background",
    "Begin Angle", "Path Angle",
    "Alignment", "Format",
    "Label",
    "Direction",
    "Fill Mode", "Style", "Fill",
    "Color Mode",
#ifdef __COLOR_RULE_H__
    "Color Rule",
#endif
    "Visibility",
    "Channel",
    "Data Color", "Distance", "XY Angle", "Z Angle",
    "Period", "Units",
    "Plot Style", "Plot Mode", "Count",
    "Stacking",
    "Image Type",
    "Text",
    "Message Label",
    "Press Message", "Release Message",
    "Image Name",
    "Data",
    "Colormap",
    "Name",
    "Line Width",
    "Precision",
    "Start Bit", "End Bit",
    "Label","visual",
    "Label/Name/Args",      /* Related Display data           */
    "X/Y/Trace Data",       /* Cartesian Plot data            */
    "Channel/Color",        /* Strip Chart data               */
    "Label/Cmd/Args",       /* Shell Command data             */
    "Axis Data",            /* Cartesian Plot axis data       */
    "Trigger Channel",      /* Cartesian Plot trigger channel */
    "Erase Channel",        /* Cartesian Plot erase channel   */
    "Erase Mode",           /* Cartesian Plot erase mode      */
};
#endif


/***
 *** resourcePaletteElements for definition of widgets associated with
 ***	various display element types.
 ***	any changes of types or ordering of above definitions, or of
 ***	DL_Element definitions in displayList.h (e.g., DL_Valuator...)
 ***	must have corresponding changes in this table!!
 ***/
#define MAX_RESOURCES_FOR_DL_ELEMENT 18
typedef struct _ResourceMap{
    Cardinal childIndexRC[MAX_RESOURCES_FOR_DL_ELEMENT];
    Cardinal numChildren;
    Widget children[MAX_RESOURCES_FOR_DL_ELEMENT];
} ResourceMap;


/***
 *** see resourcePalette.c (initializeResourcePaletteElements())
 ***    for the enumerated set of dependencies
 ***/
#ifndef ALLOCATE_STORAGE
extern ResourceMap resourcePaletteElements[NUM_DL_ELEMENT_TYPES];
#else
ResourceMap resourcePaletteElements[NUM_DL_ELEMENT_TYPES];
#endif


/***
 *** default colormap for "New..." display creation
 ***	default colormap size must be less than DL_MAX_COLORS!
 ***/
#define DEFAULT_DL_COLORMAP_SIZE	65
#ifndef ALLOCATE_STORAGE
extern DlColormap defaultDlColormap;
#else
DlColormap defaultDlColormap = {
  /* ncolors */
    65,
  /* r,  g,   b,   inten */
    {{ 255, 255, 255, 255, },
     { 236, 236, 236, 0, },
     { 218, 218, 218, 0, },
     { 200, 200, 200, 0, },
     { 187, 187, 187, 0, },
     { 174, 174, 174, 0, },
     { 158, 158, 158, 0, },
     { 145, 145, 145, 0, },
     { 133, 133, 133, 0, },
     { 120, 120, 120, 0, },
     { 105, 105, 105, 0, },
     { 90, 90, 90, 0, },
     { 70, 70, 70, 0, },
     { 45, 45, 45, 0, },
     { 0, 0, 0, 0, },
     { 0, 216, 0, 0, },
     { 30, 187, 0, 0, },
     { 51, 153, 0, 0, },
     { 45, 127, 0, 0, },
     { 33, 108, 0, 0, },
     { 253, 0, 0, 0, },
     { 222, 19, 9, 0, },
     { 190, 25, 11, 0, },
     { 160, 18, 7, 0, },
     { 130, 4, 0, 0, },
     { 88, 147, 255, 0, },
     { 89, 126, 225, 0, },
     { 75, 110, 199, 0, },
     { 58, 94, 171, 0, },
     { 39, 84, 141, 0, },
     { 251, 243, 74, 0, },
     { 249, 218, 60, 0, },
     { 238, 182, 43, 0, },
     { 225, 144, 21, 0, },
     { 205, 97, 0, 0, },
     { 255, 176, 255, 0, },
     { 214, 127, 226, 0, },
     { 174, 78, 188, 0, },
     { 139, 26, 150, 0, },
     { 97, 10, 117, 0, },
     { 164, 170, 255, 0, },
     { 135, 147, 226, 0, },
     { 106, 115, 193, 0, },
     { 77, 82, 164, 0, },
     { 52, 51, 134, 0, },
     { 199, 187, 109, 0, },
     { 183, 157, 92, 0, },
     { 164, 126, 60, 0, },
     { 125, 86, 39, 0, },
     { 88, 52, 15, 0, },
     { 153, 255, 255, 0, },
     { 115, 223, 255, 0, },
     { 78, 165, 249, 0, },
     { 42, 99, 228, 0, },
     { 10, 0, 184, 0, },
     { 235, 241, 181, 0, },
     { 212, 219, 157, 0, },
     { 187, 193, 135, 0, },
     { 166, 164, 98, 0, },
     { 139, 130, 57, 0, },
     { 115, 255, 107, 0, },
     { 82, 218, 59, 0, },
     { 60, 180, 32, 0, },
     { 40, 147, 21, 0, },
     { 26, 115, 9, 0, },
    }
};
#endif

#ifdef __COLOR_RULE_H__
/* Color Rule */
#define MAX_COLOR_RULES 16
#define MAX_SET_OF_COLOR_RULE 4
typedef struct {
    double lowerBoundary;
    double upperBoundary;
    int    colorIndex;
} colorRule_t;

typedef struct {
    colorRule_t rule[MAX_COLOR_RULES];
} setOfColorRule_t;

#ifndef ALLOCATE_STORAGE
extern setOfColorRule_t setOfColorRule[MAX_SET_OF_COLOR_RULE];
#endif
#endif

/*******************************************************************
 ********                 global variables                 *********
 *******************************************************************/

/* 
 * only one of these in all the address space
 */

/* display, connection, and miscellaneous */

EXTERN XmString dlXmStringMoreToComeSymbol;
EXTERN XmButtonType executePopupMenuButtonType[NUM_EXECUTE_POPUP_ENTRIES];
EXTERN XmString executePopupMenuButtons[NUM_EXECUTE_POPUP_ENTRIES];

EXTERN Pixel defaultForeground, defaultBackground;

/* should be dimensioned to ALARM_NSEV (alarm.h), with corresponding values */
EXTERN Pixel alarmColorPixel[4];

/* initial (default - not related to any displays) colormap */
EXTERN Pixel defaultColormap[DL_MAX_COLORS];
EXTERN Pixel *currentColormap;
EXTERN int currentColormapSize;
EXTERN Pixel unphysicalPixel;

EXTERN XFontStruct *fontTable[MAX_FONTS];
EXTERN XmFontList fontListTable[MAX_FONTS];

EXTERN DisplayInfo *displayInfoListHead, *displayInfoListTail;
EXTERN DisplayInfo *currentDisplayInfo;

/* (MDA) */
EXTERN DisplayInfo *pointerInDisplayInfo;

EXTERN ResourceBundle globalResourceBundle;
EXTERN Widget resourceEntryRC[MAX_RESOURCE_ENTRY];
EXTERN Widget resourceEntryLabel[MAX_RESOURCE_ENTRY];
EXTERN Widget resourceEntryElement[MAX_RESOURCE_ENTRY];
EXTERN Widget resourceElementTypeLabel;

EXTERN DlTraversalMode globalDisplayListTraversalMode;

EXTERN Boolean globalModifiedFlag;
				/* flag which says to traverse monitor list */

/* for object palette selections and single object selection */
EXTERN DlElementType currentElementType;

/* for clipboard/edit purposes  - note that this has objects and attributes */
#if 0
EXTERN DlElement *clipboardElementsArray;  /* array of DlElements, not ptrs */
EXTERN int numClipboardElements;
EXTERN int clipboardElementsArraySize;
EXTERN Boolean clipboardDelete;
#endif
EXTERN DlList *clipboard;

/* define MB1 semantics in the display window -
	select, or create (based on object palette selection)
*/
EXTERN ActionType currentActionType;

/* for private or shared/default colormap utilization */
EXTERN Boolean privateCmap;


#endif  /* __MEDMWIDGET_H__ */
