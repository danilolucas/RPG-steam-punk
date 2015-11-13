#include <allegro.h>

void init();
void deinit();
void reset();
void buffertimer();
void move();
void fisica();
void smoke();
void skill();
void shuriken();
void colisao(int, int, int, int);
void door(int, int, int, int, int);

BITMAP *buffer;
BITMAP *backgroundimage;
BITMAP *smokeimage;

int smokecont=1;
int shuricont=1;
int shootval=2;
int shootdirec=0;
int place;

struct player{
    int x;
    int y;
    int val;
    int direc;
    BITMAP *image;
};

player player1;

struct shoot{
    int x;
    int y;
    int val;
    int direc;
    bool cast;
    BITMAP *image;       
};
shoot shoot1;

int main() {
	init();
	reset();
	
	install_int(buffertimer, 10);
	install_int(move, 7);
	install_int(skill, 5);
	install_int(fisica, 1);
	install_int(smoke, 300);
	install_int(shuriken, 50);

	while (!key[KEY_ESC]) {
		/* put your code here */
	}

	deinit();
	return 0;
}
END_OF_MAIN()

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 540, 416, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}

	install_timer();
	install_keyboard();
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}

void reset(){
    buffer=create_bitmap(540, 416);
    backgroundimage=load_bitmap("texture/SteamPunk.bmp", NULL);
    player1.image=load_bitmap("animation/human/HumanFront.bmp", NULL);
    smokeimage=load_bitmap("animation/smoke/smoke.bmp", NULL);
    shoot1.image=load_bitmap("animation/skills/shuriken1.bmp", NULL);
    
    player1.x=200;
    player1.y=300;
    
    shoot1.x=-100;
    shoot1.y=-100;   
    
    shoot1.cast=true;
    
    place=1; 
}

void buffertimer(){
     draw_sprite(buffer, backgroundimage, 0, 0);
     draw_sprite(buffer, smokeimage, 85, -23);
     draw_sprite(buffer, shoot1.image, shoot1.x, shoot1.y);
     draw_sprite(buffer, player1.image, player1.x, player1.y);
     draw_sprite(screen, buffer, 0, 0);
     clear_bitmap(buffer);
}
END_OF_FUNCTION(buffer);
LOCK_FUNCTION(buffer);

void move(){
    if(key[KEY_UP]){
        player1.y--;
        player1.image=load_bitmap("animation/human/HumanBack.bmp", NULL);
        shoot1.val=1;
        player1.direc=1;
    }
    else{
         if(key[KEY_DOWN]){
             player1.y++;
             player1.image=load_bitmap("animation/human/HumanFront.bmp", NULL);
             shoot1.val=2;
             player1.direc=2;
         }
         else{
             if(key[KEY_RIGHT]){
                 player1.x++;
                 player1.image=load_bitmap("animation/human/HumanRight.bmp", NULL);
                 shoot1.val=3;
                 player1.direc=3;
             }
             else{
                 if(key[KEY_LEFT]){
                     player1.x--;
                     player1.image=load_bitmap("animation/human/HumanLeft.bmp", NULL);
                     shoot1.val=4;
                     player1.direc=4;
                 }
             }
         }
    }
}
END_OF_FUNCTION(move);
LOCK_FUNCTION(move);

void skill(){
    if(shoot1.cast==true){     
        if(key[KEY_1]){
            shoot1.cast=false;                   
            if(shoot1.val==1){
                shoot1.direc=1;
                shoot1.x=player1.x-10;
                shoot1.y=player1.y;
            }
            if(shoot1.val==2){
                shoot1.direc=2;
                shoot1.x=player1.x-10;
                shoot1.y=player1.y;
            }
            if(shoot1.val==3){
                shoot1.direc=3;
                shoot1.x=player1.x-10;
                shoot1.y=player1.y;
            }
            if(shoot1.val==4){
                shoot1.direc=4;
                shoot1.x=player1.x-10;
                shoot1.y=player1.y;
            }
        }
    }
    //direcao da shuriken
    if(shoot1.direc==1)
        shoot1.y--;
    if(shoot1.direc==2)
        shoot1.y++;
    if(shoot1.direc==3)
        shoot1.x++;
    if(shoot1.direc==4)
        shoot1.x--;
    //cast da shuriken
    if(shoot1.x<0)
        shoot1.cast=true;
    if(shoot1.x>540-32)
        shoot1.cast=true;
    if(shoot1.y<0)
        shoot1.cast=true;
    if(shoot1.y>416-32)
        shoot1.cast=true;
}
END_OF_FUNCTION(skill);
LOCK_FUNCTION(skill);

void fisica(){
     colisao(0, 0, 0, 540);
     colisao(0, 416, 0, 0);
     colisao(384, 416, 0, 508);
     colisao(0, 384, 508, 540);
     //colisao(paredes)
     if(place==1){
         colisao(305, 360, 170, 235);
         colisao(0, 50, 0, 305);
         colisao(0, 180, 0, 110);
         colisao(195, 416, 385, 410);
         colisao(195, 270, 255, 385);
         colisao(195, 270, 0, 150);
         colisao(270, 310, 0, 80);
         colisao(270, 310, 305, 385);
         colisao(50, 130, 155, 240);
         colisao(100, 180, 290, 380);
         colisao(5, 235, 475, 540);
         colisao(5, 110, 390, 475);
         colisao(0, 90, 350, 385);
         colisao(5, 40, 320, 350);
         //portais(postas/passagens)
         door(160, 181, 30, 60, 1);
     }
}
END_OF_FUNCTION(fisica);
LOCK_FUNCTION(fisica);

void smoke(){
    if(smokecont==1){
        smokeimage = load_bitmap("animation/smoke/smoke.bmp", NULL);
        smokecont=2;
    }
    else{
        if(smokecont==2){
            smokeimage = load_bitmap("animation/smoke/smoke2.bmp", NULL);
            smokecont=3;
        }
        else{
            if(smokecont==3){
            smokeimage = load_bitmap("animation/smoke/smoke3.bmp", NULL);
            smokecont=1;
            }
        }
    }     
}
END_OF_FUNCTION(smoke);
LOCK_FUNCTION(smoke);

void shuriken(){
     if(shuricont==1){
         shoot1.image=load_bitmap("animation/skills/shuriken1.bmp", NULL);
         shuricont=2;
     }
     else{
          if(shuricont==2){
              shoot1.image=load_bitmap("animation/skills/shuriken2.bmp", NULL);
              shuricont=3;
         }
         else{
              if(shuricont==3){
                  shoot1.image=load_bitmap("animation/skills/shuriken3.bmp", NULL);
                  shuricont=1;
              }
         }
     }
}
END_OF_FUNCTION(shuriken);
LOCK_FUNCTION(shuriken);

void colisao(int t, int h, int l, int w){
     //colisao UP
     if(player1.direc==1){
         if(player1.y<t || player1.y>h || player1.x<l || player1.x>w){
         }
         else
             player1.y++;
     }
     //colisao DOWN
     if(player1.direc==2){
         if(player1.y<t || player1.y>h || player1.x<l || player1.x>w){
         }
         else
             player1.y--;
     }
     //colisao RIGHT
     if(player1.direc==3){
         if(player1.y<t || player1.y>h || player1.x<l || player1.x>w){
         }
         else
             player1.x--;                          
     }
     //colisao LEFT
     if(player1.direc==4){
         if(player1.y<t || player1.y>h || player1.x<l || player1.x>w){
         }
         else
             player1.x++;  
     }     
}
END_OF_FUNCTION(colisao);
LOCK_FUNCTION(colisao);

void door(int t, int h, int l, int w, int d){
     if(d==1){
         if(player1.y<t || player1.y>h || player1.x<l || player1.x>w){
         }
         else{
             backgroundimage = load_bitmap("texture/House.bmp", NULL);
             d=0;
             place=2;
             player1.x=385;
             player1.y=330;
         }
     }
}
END_OF_FUNCTION(door);
LOCK_FUNCTION(door);

