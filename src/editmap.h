#ifndef EDITMAP_H
#define EDITMAP_H

#include "game.h"
#include "map.h"
#include "line.h"
#include "omdata.h"
#include "ui.h"
#include "trap.h"
#include <vector>
#include <map>
#include <list>
#include <stdarg.h>

struct real_coords;
enum field_id : int;

enum shapetype {
    editmap_rect, editmap_rect_filled, editmap_line, editmap_circle,
};

class editmap;
struct editmap_hilight {
    std::vector<bool> blink_interval;
    int cur_blink;
    nc_color color;
    std::map<tripoint, char> points;
    nc_color( *getbg )( nc_color );
    void setup()
    {
        getbg = ( color == c_red ? &red_background :
                  ( color == c_magenta ? &magenta_background :
                    ( color == c_cyan ? &cyan_background :
                      ( color == c_yellow ? &yellow_background : &green_background )
                    )
                  )
                );
    };
    void draw( editmap *em, bool update = false );
};

class editmap
{
    public:
        void uphelp( std::string txt1 = "", std::string txt2 = "", std::string title = "" );
        tripoint pos2screen( const tripoint &p );
        tripoint screen2pos( const tripoint &p );
        bool eget_direction( tripoint &p, const std::string &action ) const;
        tripoint edit();
        void uber_draw_ter( WINDOW *w, map *m );
        void update_view( bool update_info = false );
        int edit_ter();

        int edit_fld();
        int edit_trp();
        int edit_itm();
        int edit_mon();
        int edit_npc();
        int edit_veh();
        int edit_mapgen();
        void cleartmpmap( tinymap &tmpmap );
        int mapgen_preview( real_coords &tc, uimenu &gmenu );
        int mapgen_retarget();
        int select_shape( shapetype shape, int mode = -1 );

        void update_fmenu_entry( uimenu *fmenu, field *field, field_id idx );
        void setup_fmenu( uimenu *fmenu );
        bool change_fld( std::vector<tripoint> coords, field_id fid, int density );
        WINDOW *w_info;
        WINDOW *w_help;
        int width;
        int height;
        int offsetX;
        int infoHeight;

        int ter_frn_mode;
        ter_id sel_ter;
        ter_id target_ter;
        furn_id sel_frn;
        furn_id target_frn;

        tripoint recalc_target( shapetype shape );
        bool move_target( const std::string &action, int moveorigin = -1 );
        field *cur_field;

        trap_id cur_trap;

        int sel_field;
        int sel_fdensity;

        trap_id sel_trap;


        furn_id fsel;
        furn_id fset;
        trap_id trsel;
        trap_id trset;

        tripoint target;
        tripoint origin;
        bool moveall;
        bool refresh_mplans;
        shapetype editshape;

        std::string padding;

        std::map<field_id, std::string> fids;

        std::vector<tripoint> target_list;
        std::map<std::string, editmap_hilight> hilights;
        bool blink;
        bool altblink;
        int tmaxx;
        int tmaxy;
        bool uberdraw;
        std::map<oter_id, int> oter_special;

        editmap();
        ~editmap();
};

#endif
