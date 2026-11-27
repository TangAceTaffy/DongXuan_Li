#include "zf_common_headfile.h"
#include <signal.h>
#include <unistd.h>
int flag = 0;
int key_flag;
int key_distance = 0;
int Right_distance;
int Left_distance;
int Key_Right_distance;
void Button()
{
  Right_distance += Right_Encoder / 10;
  Left_distance += Left_Encoder / 10;

  if (flag == 0 && gpio_get_level(KEY_2))
  {
    if (gpio_get_level(KEY_3))
      flag = 2;

    Get_Encoder();
    ips200_show_string(2, 0 * 16, "Str_Ser_Kp");
    ips200_show_string(2, 1 * 16, "EL_Ser_Kp");
    ips200_show_string(2, 2 * 16, "Ser_Kd_d");
    ips200_show_string(2, 3 * 16, "El_Mid_Row");
    ips200_show_string(2, 4 * 16, "Str_Mid_Row");
    ips200_show_string(2, 5 * 16, "Ro_Mid_Row");
    ips200_show_string(2, 6 * 16, "Ba_Mid_Row");
    ips200_show_string(2, 7 * 16, "L_round");
    ips200_show_string(2, 8 * 16, "R_round");
    ips200_show_string(2, 9 * 16, "Str_Kp1");
    ips200_show_string(2, 10 * 16, "Els_Kp1");
    ips200_show_string(2, 11 * 16, "Ser_Kp_p");

    if (Right_distance - Key_Right_distance > 20 && Right_distance - Key_Right_distance < 40)
    {
      ips200_show_float(120, 0, Stright_Kp, 3, 1);
      ips200_show_string(200, 0 * 16, "<--");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "    ");
      ips200_show_string(200, 6 * 16, "    ");
      ips200_show_string(200, 7 * 16, "   ");
      ips200_show_string(200, 8 * 16, "   ");
      ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "   ");
      if (Float_ABS(Left_distance - key_distance) / 10 > 0.1)
      {
        Stright_Kp = Stright_Kp + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 0.1;
        key_distance = Left_distance;
        sleep(1);
      }
    }

    if (Right_distance - Key_Right_distance > 40 && Right_distance - Key_Right_distance < 60)
    {
      ips200_show_float(120, 16, Else_Kp, 3, 1);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "<--");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "    ");
      ips200_show_string(200, 6 * 16, "    ");
      ips200_show_string(200, 7 * 16, "   ");
      ips200_show_string(200, 8 * 16, "   ");
       ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "   ");

      if (Float_ABS(Left_distance - key_distance) / 10 > 0.1)
      {

        Else_Kp = Else_Kp + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 0.1;
        key_distance = Left_distance;
        sleep(1);
      }
    }

    if (Right_distance - Key_Right_distance > 60 && Right_distance - Key_Right_distance < 80)
    {
      ips200_show_float(120, 2 * 16, Kd_d, 3, 3);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "<--");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "    ");
      ips200_show_string(200, 6 * 16, "    ");
      ips200_show_string(200, 7 * 16, "   ");
      ips200_show_string(200, 8 * 16, "   ");
       ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "   ");
      if (Float_ABS(Left_distance - key_distance) / 10 > 0.001)
      {

        Kd_d = Kd_d + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 0.001;
        key_distance = Left_distance;
        sleep(1);
      }
    }

    if (Right_distance - Key_Right_distance > 80 && Right_distance - Key_Right_distance < 100)
    {
      ips200_show_float(120, 3 * 16, ElseRoad_Middle_Row, 3, 0);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "<--");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "    ");
      ips200_show_string(200, 6 * 16, "    ");
      ips200_show_string(200, 7 * 16, "   ");
      ips200_show_string(200, 8 * 16, "   ");
       ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "   ");
      if (Float_ABS(Left_distance - key_distance) / 10 > 1)
      {

        ElseRoad_Middle_Row = ElseRoad_Middle_Row + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 1;
        key_distance = Left_distance;
        sleep(1);
      }
    }

    if (Right_distance - Key_Right_distance > 100 && Right_distance - Key_Right_distance < 120)
    {
      ips200_show_float(120, 4 * 16, StrightRoad_Middle_Row, 3, 0);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "<--");
      ips200_show_string(200, 5 * 16, "    ");
      ips200_show_string(200, 6 * 16, "    ");
      ips200_show_string(200, 7 * 16, "   ");
      ips200_show_string(200, 8 * 16, "   ");
       ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "   ");
      if (Float_ABS(Left_distance - key_distance) / 10 > 1)
      {

        StrightRoad_Middle_Row = StrightRoad_Middle_Row + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 1;
        key_distance = Left_distance;
        sleep(1);
      }
    }

    if (Right_distance - Key_Right_distance > 120 && Right_distance - Key_Right_distance < 140)
    {
      ips200_show_float(120, 5 * 16, Round_Middle_Row, 3, 0);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "<--");
      ips200_show_string(200, 6 * 16, "    ");
      ips200_show_string(200, 7 * 16, "   ");
      ips200_show_string(200, 8 * 16, "   ");
       ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "   ");
      if (Float_ABS(Left_distance - key_distance) / 10 > 1)
      {

        Round_Middle_Row = Round_Middle_Row + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 1;
        key_distance = Left_distance;
        sleep(1);
      }
    }

     if (Right_distance - Key_Right_distance > 140 && Right_distance - Key_Right_distance < 160)
    {
      ips200_show_float(120, 6 * 16, Barrier_Middle_Row, 3, 0);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "   ");
      ips200_show_string(200, 6 * 16, "<--");
      ips200_show_string(200, 7 * 16, "   ");
      ips200_show_string(200, 8 * 16, "   ");
       ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "   ");
      if (Float_ABS(Left_distance - key_distance) / 10 > 1)
      {

        Barrier_Middle_Row = Barrier_Middle_Row + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 1;
        key_distance = Left_distance;
        sleep(1);
      }
    }

    if (Right_distance - Key_Right_distance > 160 && Right_distance - Key_Right_distance < 180)
    {
      ips200_show_float(120, 7 * 16, L_round_angke, 5, 0);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "    ");
      ips200_show_string(200, 6 * 16, "   ");
      ips200_show_string(200, 7 * 16, "<--");
       ips200_show_string(200, 8 * 16, "   ");
        ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "   ");
      if (Float_ABS(Left_distance - key_distance) / 10 > 1)
      {

        L_round_angke = L_round_angke + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 100;
        key_distance = Left_distance;
        sleep(1);
      }
    }

    if (Right_distance - Key_Right_distance > 180 && Right_distance - Key_Right_distance < 200)
    {
      ips200_show_float(120, 8 * 16, R_round_angke, 5, 0);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "    ");
      ips200_show_string(200, 6 * 16, "   ");
      ips200_show_string(200, 7 * 16, "   ");
       ips200_show_string(200, 8 * 16, "<--");
        ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "   ");
      if (Float_ABS(Left_distance - key_distance) / 10 > 1)
      {

        R_round_angke = R_round_angke + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 100;
        key_distance = Left_distance;
        sleep(1);
      }
    }


     if (Right_distance - Key_Right_distance > 200 && Right_distance - Key_Right_distance < 220)
    {
      ips200_show_float(120, 9 * 16, Str_Kp1, 3, 1);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "    ");
      ips200_show_string(200, 6 * 16, "   ");
      ips200_show_string(200, 7 * 16, "   ");
       ips200_show_string(200, 8 * 16, "   ");
        ips200_show_string(200, 9 * 16, "<--");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "   ");
      if (Float_ABS(Left_distance - key_distance) / 10 > 1)
      {

        Str_Kp1 = Str_Kp1 + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 0.1;
        key_distance = Left_distance;
        sleep(1);
      }
    }


     if (Right_distance - Key_Right_distance > 220 && Right_distance - Key_Right_distance < 240)
    {
      ips200_show_float(120, 10 * 16, Els_Kp1, 3, 1);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "   ");
      ips200_show_string(200, 6 * 16, "   ");
      ips200_show_string(200, 7 * 16, "   ");
      ips200_show_string(200, 8 * 16, "   ");
       ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "<--");
      ips200_show_string(200, 11 * 16, "   ");
      if (Float_ABS(Left_distance - key_distance) / 10 > 1)
      {

        Els_Kp1 = Els_Kp1 + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 0.1;
        key_distance = Left_distance;
        sleep(1);
      }
    }

      if (Right_distance - Key_Right_distance > 240 && Right_distance - Key_Right_distance < 260)
    {
      ips200_show_float(120, 11 * 16, Kp_p, 5, 3);
      ips200_show_string(200, 0 * 16, "    ");
      ips200_show_string(200, 1 * 16, "    ");
      ips200_show_string(200, 2 * 16, "    ");
      ips200_show_string(200, 3 * 16, "    ");
      ips200_show_string(200, 4 * 16, "    ");
      ips200_show_string(200, 5 * 16, "   ");
      ips200_show_string(200, 6 * 16, "   ");
      ips200_show_string(200, 7 * 16, "   ");
      ips200_show_string(200, 8 * 16, "   ");
       ips200_show_string(200, 9 * 16, "   ");
      ips200_show_string(200, 10 * 16, "   ");
      ips200_show_string(200, 11 * 16, "<--");
      if (Float_ABS(Left_distance - key_distance) / 10 > 1)
      {

        Kp_p = Kp_p + ((Left_distance - key_distance) / Float_ABS(Left_distance - key_distance)) * 0.001;
        key_distance = Left_distance;
        sleep(1);
      }
    }




  }
}
