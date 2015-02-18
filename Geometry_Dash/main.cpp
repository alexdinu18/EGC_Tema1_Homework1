/*
Dinu Marian-Alexandru
334 CC
Tema 1
*/
#include "Framework/DrawingWindow.h"
#include "Framework/Visual2D.h"
#include "Framework/Transform2D.h"
#include "Framework/Line2D.h"
#include "Framework/Rectangle2D.h"
#include "Framework/Circle2D.h"
#include "Framework/Polygon2D.h"
#include "Framework/Player.h"
#include <iostream>
#include <windows.h>


#define PI 3.14159265358979323846
#define TRANSLATION_SPEED -2.5
using namespace std;

Visual2D *v2d1, *v2d2;
Rectangle2D *background;
Player *player;
std::vector <Rectangle2D*> platforms;
std::vector <Circle2D*> circles;
std::vector <Polygon2D*> triangles;
std::vector <Line2D*> flags;
Text* end_game, *nr_points, *remaining, *lives;
int points = 0;
int nr_lives = 3,prev_nr_lives = nr_lives;
float plat_x2 = 0.0, plat_y2 = 0.0;

float x_max = 500, previous_x_flag = 0.0;
bool once = true;

// functia care updateaza textul de pe ecran
void update_text() {
	DrawingWindow::removeText_from_Visual2D(nr_points, v2d1);
	DrawingWindow::removeText_from_Visual2D(remaining, v2d1);
	DrawingWindow::removeText_from_Visual2D(lives, v2d1);
	DrawingWindow::removeText(nr_points);
	DrawingWindow::removeText(remaining);
	DrawingWindow::removeText(lives);

	switch(nr_lives) {
		case 3:
			{
				lives = new Text("Lives: 3", Point2D(x_max - 100.0, 365.0), Color(0,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(lives, v2d1);
				break;
			}
		case 2:
			{
				lives = new Text("Lives: 2", Point2D(x_max - 100.0, 365.0), Color(0,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(lives, v2d1);
				break;
			}
		case 1:
			{
				lives = new Text("Lives: 1", Point2D(x_max - 100.0, 365.0), Color(0,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(lives, v2d1);
				break;
			}
		case 0:
			{
				lives = new Text("Lives: 0", Point2D(x_max - 100.0, 365.0), Color(0,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(lives, v2d1);
				Text* game_over = new Text("GAME OVER!", Point2D(x_max - 300.0, 250.0), Color(255,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(game_over, v2d1);
				break;
			}

	}

	switch (points) {
		case 0:
			{
				nr_points = new Text("Nr. Points: 0", Point2D(x_max - 300.0,380.0), Color(0,0,0), BITMAP_HELVETICA_18);
				remaining = new Text("Remaining: 5", Point2D(x_max - 300.0, 350.0), Color(0,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(nr_points, v2d1);
				DrawingWindow::addText_to_Visual2D(remaining, v2d1);
				break;
			}

		case 1:
			{
				nr_points = new Text("Nr. Points: 1", Point2D(x_max - 300.0,380.0), Color(0,0,0), BITMAP_HELVETICA_18);
				remaining = new Text("Remaining: 4", Point2D(x_max - 300.0, 350.0), Color(0,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(nr_points, v2d1);
				DrawingWindow::addText_to_Visual2D(remaining, v2d1);
				break;
			}

		case 2:
			{
				nr_points = new Text("Nr. Points: 2", Point2D(x_max - 300.0,380.0), Color(0,0,0), BITMAP_HELVETICA_18);
				remaining = new Text("Remaining: 3", Point2D(x_max - 300.0, 350.0), Color(0,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(nr_points, v2d1);
				DrawingWindow::addText_to_Visual2D(remaining, v2d1);
				break;
			}

		case 3:
			{
				nr_points = new Text("Nr. Points: 3", Point2D(x_max - 300.0,380.0), Color(0,0,0), BITMAP_HELVETICA_18);
				remaining = new Text("Remaining: 2", Point2D(x_max - 300.0, 350.0), Color(0,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(nr_points, v2d1);
				DrawingWindow::addText_to_Visual2D(remaining, v2d1);
				break;
			}

		case 4:
			{
				nr_points = new Text("Nr. Points: 4", Point2D(x_max - 300.0,380.0), Color(0,0,0), BITMAP_HELVETICA_18);
				remaining = new Text("Remaining: 1", Point2D(x_max - 300.0, 350.0), Color(0,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(nr_points, v2d1);
				DrawingWindow::addText_to_Visual2D(remaining, v2d1);
				break;
			}

		case 5:
			{
				nr_points = new Text("Nr. Points: 5", Point2D(x_max - 300.0,380.0), Color(0,0,0), BITMAP_HELVETICA_18);
				remaining = new Text("Remaining: 0", Point2D(x_max - 300.0, 350.0), Color(0,0,0), BITMAP_HELVETICA_18);
				DrawingWindow::addText_to_Visual2D(nr_points, v2d1);
				DrawingWindow::addText_to_Visual2D(remaining, v2d1);	
				break;
			}
	}

	if (x_max > 3300 && once) {
		once = false;
		if (points == 5)
			end_game = new Text("Congratulations! You've just won the game!", Point2D(3550.0, 200.0), Color(0,200,200), BITMAP_HELVETICA_18);
		else		
			end_game = new Text("The game is over, but you've missed some point(s)!", Point2D(3550.0, 200.0), Color(0,200,200), BITMAP_HELVETICA_18);
		
		DrawingWindow::addText_to_Visual2D(end_game, v2d1);
	}
}

//functia care permite adaugarea de obiecte
void DrawingWindow::init()
{
	
	v2d1 = new Visual2D(0.0, 0.0, 8*(float)DrawingWindow::width, (float)DrawingWindow::height, 0.0, 0.0, (float)DrawingWindow::width, (float)DrawingWindow::height);
	v2d1->cadruFereastra(Color(1,0,0));
	v2d1->tipTran(true);
	addVisual2D(v2d1);
	
	player = new Player(DrawingWindow::width / 5.0 - PLAYER_WIDTH / 2.0, 0.0);//25.0);
	addObject2D_to_Visual2D(player->eye2, v2d1);
	addObject2D_to_Visual2D(player->eye1, v2d1);
	addObject2D_to_Visual2D(player->mouth, v2d1);
	addObject2D_to_Visual2D(player->body, v2d1);

	// initializari
	// platforme
	platforms.push_back(new Rectangle2D(Point2D(250.0,0.0), 250.0, 25.0,Color(0,0,255),true));
	platforms.push_back(new Rectangle2D(Point2D(500.0,50.0), 250.0, 25.0,Color(0,0,255),true));
	platforms.push_back(new Rectangle2D(Point2D(1020.0,0.0), 100.0, 25.0,Color(0,0,255),true));
	platforms.push_back(new Rectangle2D(Point2D(1500.0,0.0), 500.0, 25.0,Color(0,0,255),true));
	platforms.push_back(new Rectangle2D(Point2D(2000.0,25.0), 500.0, 25.0,Color(0,0,255),true));
	platforms.push_back(new Rectangle2D(Point2D(2750.0,0.0), 250.0, 25.0,Color(0,0,255),true));
	platforms.push_back(new Rectangle2D(Point2D(3000.0,25.0), 250.0, 25.0,Color(0,0,255),true));
	platforms.push_back(new Rectangle2D(Point2D(3250.0,50.0), 250.0, 25.0,Color(0,0,255),true));

	// cercuri
	circles.push_back(new Circle2D(Point2D(850.0, 10.0), 10.0, Color(255,0,0), true));
	circles.push_back(new Circle2D(Point2D(1130.0, 35.0), 10.0, Color(255,0,0), true));
	circles.push_back(new Circle2D(Point2D(1150.0, 35.0), 10.0, Color(255,0,0), true));
	circles.push_back(new Circle2D(Point2D(1170.0, 35.0), 10.0, Color(255,0,0), true));
	circles.push_back(new Circle2D(Point2D(1190.0, 35.0), 10.0, Color(255,0,0), true));
	circles.push_back(new Circle2D(Point2D(2730.0, 10.0), 10.0, Color(255,0,0), true));
	
	// triunghiuri
	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[0]->addPoint(Point2D(235.0,0.0));
	triangles[0]->addPoint(Point2D(250.0,0.0));
	triangles[0]->addPoint(Point2D(242.5,25.0));

	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[1]->addPoint(Point2D(750.0,0.0));
	triangles[1]->addPoint(Point2D(765.0,0.0));
	triangles[1]->addPoint(Point2D(757.5,25.0));

	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[2]->addPoint(Point2D(765.0,0.0));
	triangles[2]->addPoint(Point2D(780.0,0.0));
	triangles[2]->addPoint(Point2D(772.5,25.0));

	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[3]->addPoint(Point2D(780.0,0.0));
	triangles[3]->addPoint(Point2D(795.0,0.0));
	triangles[3]->addPoint(Point2D(787.5,25.0));

	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[4]->addPoint(Point2D(795.0,0.0));
	triangles[4]->addPoint(Point2D(810.0,0.0));
	triangles[4]->addPoint(Point2D(802.5,25.0));
	
	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[5]->addPoint(Point2D(0.0,0.0));
	triangles[5]->addPoint(Point2D(15.0,0.0));
	triangles[5]->addPoint(Point2D(7.5,25.0));
	
	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[6]->addPoint(Point2D(1105.0,25.0));
	triangles[6]->addPoint(Point2D(1120.0,25.0));
	triangles[6]->addPoint(Point2D(1112.5,50.0));

	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[7]->addPoint(Point2D(1120.0,0.0));
	triangles[7]->addPoint(Point2D(1135.0,0.0));
	triangles[7]->addPoint(Point2D(1127.5,25.0));

	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[8]->addPoint(Point2D(1135.0,0.0));
	triangles[8]->addPoint(Point2D(1150.0,0.0));
	triangles[8]->addPoint(Point2D(1142.5,25.0));

	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[9]->addPoint(Point2D(1150.0,0.0));
	triangles[9]->addPoint(Point2D(1165.0,0.0));
	triangles[9]->addPoint(Point2D(1157.5,25.0));

	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[10]->addPoint(Point2D(1165.0,0.0));
	triangles[10]->addPoint(Point2D(1180.0,0.0));
	triangles[10]->addPoint(Point2D(1172.5,25.0));

	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[11]->addPoint(Point2D(1180.0,0.0));
	triangles[11]->addPoint(Point2D(1195.0,0.0));
	triangles[11]->addPoint(Point2D(1187.5,25.0));

	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[12]->addPoint(Point2D(1750.0,25.0));
	triangles[12]->addPoint(Point2D(1765.0,25.0));
	triangles[12]->addPoint(Point2D(1757.5,50.0));


	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[13]->addPoint(Point2D(2100.0,50.0));
	triangles[13]->addPoint(Point2D(2115.0,50.0));
	triangles[13]->addPoint(Point2D(2107.5,75.0));


	triangles.push_back(new Polygon2D(Color(0,0,0), true));
	triangles[14]->addPoint(Point2D(2450.0,50.0));
	triangles[14]->addPoint(Point2D(2465.0,50.0));
	triangles[14]->addPoint(Point2D(2457.5,75.0));

	// steaguri
	flags.push_back(new Line2D(Point2D(275.0,25.0), Point2D(275.0,75.0)));
	flags.push_back(new Line2D(Point2D(275.0,70.0), Point2D(300.0,60.0)));
	flags.push_back(new Line2D(Point2D(275.0,50.0), Point2D(300.0,60.0)));

	flags.push_back(new Line2D(Point2D(920.0,0.0), Point2D(920.0,50.0)));
	flags.push_back(new Line2D(Point2D(920.0,45.0), Point2D(945.0,35.0)));
	flags.push_back(new Line2D(Point2D(920.0,25.0), Point2D(945.0,35.0)));

	flags.push_back(new Line2D(Point2D(1600.0,25.0), Point2D(1600.0,75.0)));
	flags.push_back(new Line2D(Point2D(1600.0,70.0), Point2D(1625,60.0)));
	flags.push_back(new Line2D(Point2D(1600.0,50.0), Point2D(1625,60.0)));

	flags.push_back(new Line2D(Point2D(2300.0,50.0), Point2D(2300.0,100.0)));
	flags.push_back(new Line2D(Point2D(2300.0,95.0), Point2D(2325,85.0)));
	flags.push_back(new Line2D(Point2D(2300.0,75.0), Point2D(2325,85.0)));

	flags.push_back(new Line2D(Point2D(2850.0,25.0), Point2D(2850,75.0)));
	flags.push_back(new Line2D(Point2D(2850.0,70.0), Point2D(2875,60.0)));
	flags.push_back(new Line2D(Point2D(2850.0,50.0), Point2D(2875,60.0)));

	// adaugarea obiectelor in contextul vizual
	for (int i = 0, n = platforms.size(); i < n; i ++)
		addObject2D_to_Visual2D(platforms[i], v2d1);

	for (int i = 0, n = circles.size(); i < n; i ++)
		addObject2D_to_Visual2D(circles[i], v2d1);

	for (int i = 0, n = triangles.size(); i < n; i ++)
		addObject2D_to_Visual2D(triangles[i], v2d1);

	for (int i = 0, n = flags.size(); i < n; i ++)
		addObject2D_to_Visual2D(flags[i], v2d1);


	nr_points = new Text("Nr. Points: 0", Point2D(200.0,380.0), Color(0,0,0), BITMAP_HELVETICA_18);
	remaining = new Text("Remaining: 5", Point2D(200.0, 350.0), Color(0,0,0), BITMAP_HELVETICA_18);
	lives = new Text("Lives: 3", Point2D(400.0, 365.0), Color(0,0,0), BITMAP_HELVETICA_18);
	
	addText_to_Visual2D(nr_points,v2d1);
	addText_to_Visual2D(remaining,v2d1);
	addText_to_Visual2D(lives,v2d1);

	v2d1->fereastra(0.0, 0.0, (float)DrawingWindow::width, (float)DrawingWindow::height-100);
	
	// Eliminati comentariul de mai jos pentru muzica de fundal
	PlaySound(TEXT("beat.wav"), NULL, SND_FILENAME | SND_ASYNC);
}


// functia care permite animatia
void DrawingWindow::onIdle()
{	
	if (nr_lives > 0) {
		
		for (int i = 0, n = circles.size(); i < n; i ++) {
			if (player->collision_detector(circles[i])) {
				//std::cout << "true = coliziune cu CERC\n";
			}
		}
		
		for (int i = 0, n = flags.size(); i < n; i ++) {
			if (player->collision_detector(flags[i])) {
				if (flags[i]->points[0]->x > previous_x_flag + 26.0) {
					previous_x_flag = flags[i]->points[0]->x;
					points++;
				}
			}
		}

		// caderea de pe platforme
		if (player->y > 0 && player->jmp == false && player->x > plat_x2) {
				player->y -= 5.0;
				if (player->y < 0)
					player->y = 0;
		}
			
		for (int i = 0, n = platforms.size(); i < n; i ++) {
			if (player->collision_detector(platforms[i])) {
				if (!player->land_on_platform) {
					nr_lives--;
					
					if (nr_lives) {
						switch(points) {
							case 0 : {
								x_max = 500.0;
								player->x = 75.0;
								player->y = 0.0;
								player->jmp = false;
								break;
							}
							case 1 : {
								x_max = 725.0;
								player->x = 300.0;
								player->y = 25.0;
								player->jmp = false;
								break;
							}
							case 2 : {
								x_max = 1400.0;
								player->x = 950.0;
								player->y = 0.0;
								player->jmp = false;
								break;
							}
							case 3 : {
								x_max = 2080.0;
								player->x = 1630.0;
								player->y = 25.0;
								player->jmp = false;
								break;
							}
							case 4 : {
								x_max = 2580.0;
								player->x = 2330.0;
								player->y = 50.0;
								player->jmp = false;
								break;
							}
							case 5 : {
								x_max = 3300.0;
								player->x = 2880.0;
								player->y = 25.0;
								player->jmp = false;
								break;
							}
						}
					}
				}

				if (player->land_on_platform) {
					plat_x2 = platforms[i]->points[2]->x;
					plat_y2 = platforms[i]->points[2]->y;
				}
				
			}
	}
	
			
		for (int i = 0, n = triangles.size(); i < n; i ++)
			if (player->collision_detector(triangles[i])) {
				nr_lives--;
				
				if (nr_lives) {
					switch(points) {
						case 0 : {
							x_max = 500.0;
							player->x = 75.0;
							player->y = 0.0;
							player->jmp = false;
							break;
						}
						case 1 : {
							x_max = 725.0;
							player->x = 300.0;
							player->y = 25.0;
							player->jmp = false;
							break;
						}
						case 2 : {
							x_max = 1400.0;
							player->x = 950.0;
							player->y = 0.0;
							player->jmp = false;
							break;
						}
						case 3 : {
							x_max = 2080.0;
							player->x = 1630.0;
							player->y = 25.0;
							player->jmp = false;
							break;
						}
						case 4 : {
							x_max = 2580.0;
							player->x = 2330.0;
							player->y = 50.0;
							player->jmp = false;
							break;
						}
						case 5 : {
							x_max = 3300.0;
							player->x = 2880.0;
							player->y = 25.0;
							player->jmp = false;
							break;
						}
					}
				}
			}
	
	
		if (x_max <= 4000) {
			v2d1->fereastra(x_max - 500, 0.0, x_max, 400.0);
			x_max += 2;
			player->x += 2.0;

				Transform2D::loadIdentityMatrix();
				Transform2D::translateMatrix(player->x - 75, player->y);

				Transform2D::applyTransform(player->body);
				Transform2D::applyTransform(player->mouth);
				Transform2D::applyTransform(player->eye1);
				Transform2D::applyTransform(player->eye2);

		}

			player->jump();


		player->land_on_platform = false;
			
		if (prev_nr_lives > nr_lives && nr_lives > 0) {
			prev_nr_lives = nr_lives;
			Sleep(2000);
		}
		update_text();

		
	}
}



//functia care se apeleaza la redimensionarea ferestrei
void DrawingWindow::onReshape(int width,int height)
{
	v2d1->poarta(0,0,width, height);
	// TODO:	modificati astfel incat sa mearga pentru toate cele 4 contexte vizuale
}

//functia care defineste ce se intampla cand se apasa pe tastatura
void DrawingWindow::onKey(unsigned char key)
{
	switch(key)
	{
		case KEY_ESC : exit(0);
		case KEY_SPACE : {
			if (player->y == 0.0 || player->y == 25.0 || player->y == 50.0 || player->y == 75.0) {
				player->jmp = true;
				player->step = 0.0;
				break;
			}
		}
	}
}

//functia care defineste ce se intampla cand se da click pe mouse
void DrawingWindow::onMouse(int button,int state,int x, int y)
{
	// TODO:	proceseaza click-ul pentru a spune in care dintre cele 4 contexte vizuale s-a dat click
	//			+ daca s-a dat click in interiorul dreptunghiului 

	// Exemplu de cum se pot parcurge toate contextele vizuale
	/*
	for (int i = 0; i < visuals2D.size(); i++)
	{
		... = visuals2D[i]->...;
		... = visuals2D[i]->...;
	}
	*/
}



int main(int argc, char** argv)
{
	//creare fereastra
	DrawingWindow dw(argc, argv, 500, 500, 300, 100, "Geometry Dash");
	//se apeleaza functia init() - in care s-au adaugat obiecte
	dw.init();
	//se intra in bucla principala de desenare - care face posibila desenarea, animatia si procesarea evenimentelor
	dw.run();
	return 0;

}