#include "DGenerator.h"

MMap DGenerator::generate(int Width, int Height)
{
	MMap map;
	map.width = Width;
	map.height = Height;

	for (int i=0; i<Width; i++)
	{
		std::vector<MCell> tmp_obj;
		MCell mcell;
		mcell.ground = flor;
		mcell.eniv = empty;
		mcell.npc = empty;

		for (int k=0; k<Height; k++)
		{

			tmp_obj.push_back(mcell); 
		}
		map.cells.push_back(tmp_obj); // add objects to object list
	}
	
    //---------------Npc-----------------
	map.cells[8][10].npc = npc;
	map.cells[8][9].npc = npc;
	map.cells[8][8].npc = npc;
	map.cells[8][7].npc = npc;
	map.cells[8][6].npc = npc;
	map.cells[8][5].npc = npc;
	map.cells[8][4].npc = npc;
	map.cells[8][3].npc = npc;
	map.cells[8][2].npc = npc;
	map.cells[8][1].npc = npc;
	
	//---------------Left wall-----------
	map.cells[11][11].eniv = wall;
	map.cells[11][12].eniv = wall;
	map.cells[11][13].eniv = wall;
	map.cells[11][14].eniv = wall;
	map.cells[11][15].eniv = wall;
	map.cells[11][16].eniv = wall;
	map.cells[11][17].eniv = wall;
	map.cells[11][18].eniv = wall;
	map.cells[11][19].eniv = wall;
	map.cells[11][20].eniv = wall;

	//---------------Right wall-----------
	map.cells[20][11].eniv = wall;
	map.cells[20][12].eniv = wall;
	map.cells[20][13].eniv = wall;
	map.cells[20][14].eniv = wall;
	map.cells[20][15].eniv = wall;
	map.cells[20][16].eniv = wall;
	map.cells[20][17].eniv = wall;
	map.cells[20][18].eniv = wall;
	map.cells[20][19].eniv = wall;
	map.cells[20][20].eniv = wall;

	//---------------Top wall-----------
	map.cells[11][11].eniv = wall;
	map.cells[12][11].eniv = wall;
	map.cells[13][11].eniv = wall;
	map.cells[14][11].eniv = wall;
	map.cells[15][11].eniv = wall;
	map.cells[16][11].eniv = wall;
	map.cells[17][11].eniv = wall;
	map.cells[18][11].eniv = wall;
	map.cells[19][11].eniv = wall;
	map.cells[20][11].eniv = wall;

	//---------------Bottom wall-----------
	map.cells[11][20].eniv = wall;
	map.cells[12][20].eniv = wall;
	map.cells[13][20].eniv = wall;
	map.cells[14][20].eniv = wall;
	map.cells[15][20].eniv = wall;
	map.cells[16][20].eniv = wall;
	map.cells[17][20].eniv = wall;
	map.cells[18][20].eniv = wall;
	map.cells[19][20].eniv = wall;
	map.cells[20][20].eniv = wall;

	return map;
}