#include <stdint.h>
#include "graphics.h"

void draw_cat(int x, int y, double size, uint8_t color) {
    size*=-1;
    gfx_cubic_bezier(x + size * (-2.782089), y + size * (0.728882), x + size * (-2.687286), y + size * (0.487578), x + size * (-2.519882), y + size * (-0.143848), x + size * (-2.260941), y + size * (-0.156696), color);
    gfx_cubic_bezier(x + size * (-2.260941), y + size * (-0.156696), x + size * (-2.002003), y + size * (-0.169544), x + size * (-2.592766), y + size * (-1.940506), x + size * (-2.333832), y + size * (-1.953369), color);
    gfx_cubic_bezier(x + size * (-2.333832), y + size * (-1.953369), x + size * (-2.074891), y + size * (-1.966233), x + size * (-2.031536), y + size * (-0.588455), x + size * (-1.772598), y + size * (-0.601311), color);
    gfx_cubic_bezier(x + size * (-1.772598), y + size * (-0.601311), x + size * (-1.513661), y + size * (-0.614166), x + size * (-1.842030), y + size * (-2.053482), x + size * (-1.583093), y + size * (-2.066330), color);
    gfx_cubic_bezier(x + size * (-1.583093), y + size * (-2.066330), x + size * (-1.324153), y + size * (-2.079178), x + size * (-1.597475), y + size * (-0.594513), x + size * (-0.799553), y + size * (-0.634109), color);
    gfx_cubic_bezier(x + size * (-0.799553), y + size * (-0.634109), x + size * (-0.400597), y + size * (-0.653908), x + size * (-0.241974), y + size * (-0.585724), x + size * (-0.196793), y + size * (-0.814415), color);
    gfx_cubic_bezier(x + size * (-0.196793), y + size * (-0.814415), x + size * (-0.151611), y + size * (-1.043106), x + size * (-0.411095), y + size * (-1.982803), x + size * (-0.252907), y + size * (-1.978867), color);
    gfx_cubic_bezier(x + size * (-0.252907), y + size * (-1.978867), x + size * (0.063477), y + size * (-1.970993), x + size * (0.004211), y + size * (-0.138706), x + size * (0.206284), y + size * (-0.816322), color);
    gfx_cubic_bezier(x + size * (0.206284), y + size * (-0.816322), x + size * (0.408357), y + size * (-1.493942), x + size * (0.603409), y + size * (-1.150269), x + size * (0.661835), y + size * (-1.854965), color);
    gfx_cubic_bezier(x + size * (0.661835), y + size * (-1.854965), x + size * (0.720261), y + size * (-2.559661), x + size * (0.860352), y + size * (-2.346375), x + size * (0.829468), y + size * (-1.639954), color);
    gfx_cubic_bezier(x + size * (0.829468), y + size * (-1.639954), x + size * (0.798583), y + size * (-0.933517), x + size * (0.209198), y + size * (-1.236145), x + size * (0.709198), y + size * (-0.736145), color);
    gfx_cubic_bezier(x + size * (0.709198), y + size * (-0.736145), x + size * (1.209196), y + size * (-0.236147), x + size * (1.436188), y + size * (-0.739677), x + size * (1.696075), y + size * (0.225961), color);
    gfx_cubic_bezier(x + size * (1.696075), y + size * (0.225961), x + size * (1.955963), y + size * (1.191597), x + size * (2.339386), y + size * (1.611008), x + size * (2.086029), y + size * (1.734726), color);
    gfx_cubic_bezier(x + size * (2.086029), y + size * (1.734726), x + size * (1.832647), y + size * (1.858456), x + size * (1.418488), y + size * (0.047750), x + size * (1.153076), y + size * (-0.047365), color);
    gfx_cubic_bezier(x + size * (1.153076), y + size * (-0.047365), x + size * (0.887637), y + size * (-0.142491), x + size * (0.293793), y + size * (-0.283123), x + size * (0.256561), y + size * (-0.003633), color);
    gfx_cubic_bezier(x + size * (0.256561), y + size * (-0.003633), x + size * (0.219330), y + size * (0.275857), x + size * (-1.484654), y + size * (0.001139), x + size * (-1.521888), y + size * (0.280626), color);
    gfx_cubic_bezier(x + size * (-1.521888), y + size * (0.280626), x + size * (-1.559121), y + size * (0.560112), x + size * (-1.361159), y + size * (0.972740), x + size * (-1.572908), y + size * (1.158913), color);
    gfx_cubic_bezier(x + size * (-1.572908), y + size * (1.158913), x + size * (-1.784662), y + size * (1.345089), x + size * (-1.311937), y + size * (1.803970), x + size * (-1.551043), y + size * (1.654541), color);
    gfx_cubic_bezier(x + size * (-1.551043), y + size * (1.654541), x + size * (-1.790144), y + size * (1.505114), x + size * (-1.738327), y + size * (1.512428), x + size * (-1.977432), y + size * (1.362999), color);
    gfx_cubic_bezier(x + size * (-1.977432), y + size * (1.362999), x + size * (-2.216537), y + size * (1.213570), x + size * (-2.249428), y + size * (1.046837), x + size * (-2.531372), y + size * (1.049583), color);
    gfx_cubic_bezier(x + size * (-2.531372), y + size * (1.049583), x + size * (-2.813324), y + size * (1.052330), x + size * (-3.108597), y + size * (1.301254), x + size * (-2.950470), y + size * (1.067802), color);
    gfx_cubic_bezier(x + size * (-2.950470), y + size * (1.067802), x + size * (-2.792351), y + size * (0.834363), x + size * (-2.927292), y + size * (0.965874), x + size * (-2.786484), y + size * (0.721592), color);
    gfx_cubic_bezier(x + size * (-2.506935), y + size * (0.600712), x + size * (-2.568062), y + size * (0.837290), x + size * (-2.450577), y + size * (0.796780), x + size * (-2.237602), y + size * (0.661659), color);
    gfx_cubic_bezier(x + size * (-2.237602), y + size * (0.661659), x + size * (-2.024630), y + size * (0.526541), x + size * (-2.428833), y + size * (0.356236), x + size * (-2.506256), y + size * (0.596283), color);
    gfx_cubic_bezier(x + size * (-1.643602), y + size * (0.780918), x + size * (-1.644619), y + size * (1.025261), x + size * (-1.747952), y + size * (0.956223), x + size * (-1.919582), y + size * (0.771397), color);
    gfx_cubic_bezier(x + size * (-1.919582), y + size * (0.771397), x + size * (-2.091211), y + size * (0.586573), x + size * (-1.656998), y + size * (0.524618), x + size * (-1.643135), y + size * (0.776459), color);
    gfx_cubic_bezier(x + size * (-1.812840), y + size * (0.750748), x + size * (-1.812840), y + size * (0.771753), x + size * (-1.795801), y + size * (0.788792), x + size * (-1.774796), y + size * (0.788792), color);
    gfx_cubic_bezier(x + size * (-1.774796), y + size * (0.788792), x + size * (-1.753790), y + size * (0.788792), x + size * (-1.736752), y + size * (0.771753), x + size * (-1.736752), y + size * (0.750748), color);
    gfx_cubic_bezier(x + size * (-1.736752), y + size * (0.750748), x + size * (-1.736752), y + size * (0.729743), x + size * (-1.753790), y + size * (0.712704), x + size * (-1.774796), y + size * (0.712704), color);
    gfx_cubic_bezier(x + size * (-1.774796), y + size * (0.712704), x + size * (-1.795801), y + size * (0.712704), x + size * (-1.812840), y + size * (0.729743), x + size * (-1.812840), y + size * (0.750748), color);
    gfx_cubic_bezier(x + size * (-2.377716), y + size * (0.612263), x + size * (-2.377716), y + size * (0.633269), x + size * (-2.360674), y + size * (0.650308), x + size * (-2.339668), y + size * (0.650307), color);
    gfx_cubic_bezier(x + size * (-2.339668), y + size * (0.650307), x + size * (-2.318664), y + size * (0.650306), x + size * (-2.301628), y + size * (0.633267), x + size * (-2.301628), y + size * (0.612263), color);
    gfx_cubic_bezier(x + size * (-2.301628), y + size * (0.612263), x + size * (-2.301628), y + size * (0.591259), x + size * (-2.318664), y + size * (0.574220), x + size * (-2.339668), y + size * (0.574219), color);
    gfx_cubic_bezier(x + size * (-2.339668), y + size * (0.574219), x + size * (-2.360674), y + size * (0.574218), x + size * (-2.377716), y + size * (0.591257), x + size * (-2.377716), y + size * (0.612263), color);
    gfx_cubic_bezier(x + size * (-1.997910), y + size * (0.373056), x + size * (-1.987803), y + size * (0.398244), x + size * (-2.019005), y + size * (0.430635), x + size * (-2.027046), y + size * (0.436172), color);
    gfx_cubic_bezier(x + size * (-2.027046), y + size * (0.436172), x + size * (-2.067259), y + size * (0.463862), x + size * (-2.423798), y + size * (0.363961), x + size * (-2.416718), y + size * (0.333735), color);
    gfx_cubic_bezier(x + size * (-2.416718), y + size * (0.333735), x + size * (-2.409877), y + size * (0.304529), x + size * (-2.162384), y + size * (0.369557), x + size * (-2.035446), y + size * (0.412331), color);
    gfx_cubic_bezier(x + size * (-2.035446), y + size * (0.412331), x + size * (-2.010059), y + size * (0.420885), x + size * (-1.999018), y + size * (0.433633), x + size * (-1.973560), y + size * (0.441977), color);
    gfx_cubic_bezier(x + size * (-1.973560), y + size * (0.441977), x + size * (-1.846272), y + size * (0.483696), x + size * (-1.586575), y + size * (0.534006), x + size * (-1.592718), y + size * (0.513920), color);
    gfx_cubic_bezier(x + size * (-1.592718), y + size * (0.513920), x + size * (-1.598862), y + size * (0.493834), x + size * (-1.935053), y + size * (0.568934), x + size * (-1.997402), y + size * (0.450375), color);
    gfx_cubic_bezier(x + size * (-1.997402), y + size * (0.450375), x + size * (-2.009872), y + size * (0.426663), x + size * (-1.991536), y + size * (0.400824), x + size * (-1.967754), y + size * (0.388488), color);
    gfx_cubic_bezier(x + size * (-1.967754), y + size * (0.388488), x + size * (-1.848846), y + size * (0.326807), x + size * (-1.607707), y + size * (0.469498), x + size * (-1.598152), y + size * (0.450792), color);
    gfx_cubic_bezier(x + size * (-1.598152), y + size * (0.450792), x + size * (-1.588597), y + size * (0.432087), x + size * (-1.832104), y + size * (0.447526), x + size * (-1.959358), y + size * (0.412331), color);
    gfx_cubic_bezier(x + size * (-1.959358), y + size * (0.412331), x + size * (-1.984809), y + size * (0.405292), x + size * (-1.996712), y + size * (0.394875), x + size * (-2.020737), y + size * (0.383915), color);
    gfx_cubic_bezier(x + size * (-2.020737), y + size * (0.383915), x + size * (-2.140859), y + size * (0.329115), x + size * (-2.367607), y + size * (0.204998), x + size * (-2.376999), y + size * (0.223784), color);
    gfx_cubic_bezier(x + size * (-2.376999), y + size * (0.223784), x + size * (-2.386392), y + size * (0.242573), x + size * (-2.048445), y + size * (0.247116), x + size * (-1.997910), y + size * (0.373056), color);
}

