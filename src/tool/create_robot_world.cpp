#include <cell_world/paths.h>
#include <cell_world/map.h>
#include <cell_world.h>
#include <iostream>
#include <vector>

using namespace std;
using namespace cell_world;

vector<int> get_pattern(int start){
    /* given occluded cell in hex circle return the cells that need to be checked for occlusions*/
    int pattern_array[] = {2,3,4,5,0,1,2,3};
    vector<int> concat_pattern;
    for (int i = start; i<=(start+2); i++){
        concat_pattern.push_back(pattern_array[i]); // append
    }
    return concat_pattern;
}

bool adj_occlusions(auto &coord, Map &map1){
    int cell_num = 0;
    int wall_count = 0;
    Coordinates cell;

    // create coordinate array
    Coordinates ne = Coordinates(coord.x + 1, coord.y + 1);
    Coordinates e = Coordinates(coord.x + 2, coord.y);
    Coordinates se = Coordinates(coord.x + 1, coord.y - 1);
    Coordinates sw = Coordinates(coord.x - 1, coord.y - 1);
    Coordinates w = Coordinates(coord.x - 2, coord.y);
    Coordinates nw = Coordinates(coord.x - 1, coord.y + 1);
    Coordinates new_coordinates[] = {ne, e, se, sw, w, nw};

    // loop through all surrounding cells
    for (auto &c: new_coordinates){
        // check if new coordinate is in world
        if (map1.find(c) != Not_found) {
            // check if new coordinate is occluded
            if (map1[c].occluded) {
                // get pattern to check
                auto check_cells= get_pattern(cell_num);
                // check nonadjacent cells of the found occluded cell
                for (int i:check_cells) {
                    cell = new_coordinates[i];
                    // check if cell exists in world
                    if (map1.find(cell) == Not_found){
                        // if hexagon is against a wall at least 2 of the surrounding cells DNE
                        if (wall_count > 0) return true;
                        wall_count ++;
                    }
                        // if cell exists in the world check if occluded
                    else if (map1[cell].occluded) return true;
                }
            }
        }
        cell_num++;
    }
    return false;
}


int main(){

    // load world and create new_world to modify
    string occlusions_name = "22_01";

    auto wc = Resources::from("world_configuration").key("hexagonal").get_resource<World_configuration>();
    auto wi = Resources::from("world_implementation").key("hexagonal").key("mice").get_resource<World_implementation>();
    auto occlusions = Resources::from("cell_group").key("hexagonal").key(occlusions_name).key("occlusions").get_resource<Cell_group_builder>();
    World world1(wc, wi, occlusions);
    World world2 = world1;

    // modify world by occluding cells
    Cell_group cg1 = world1.create_cell_group();
    Cell_group cg2 = world2.create_cell_group();
    Map map1 (cg1);
    Map map2 (cg2);

    // find all free cells in world
    auto free_cells = map2.cells.free_cells();

    // occlude cells that are not navigable
    for(auto &cell : free_cells){
        //cout << cell << endl;
        bool occluded_bool = adj_occlusions(cell.get().coordinates, map1);
        int index = map2.find(cell.get().coordinates);
        if (occluded_bool){
            world2.cells[index].occluded = true;
            cout << "new fake occlusions ...................."<< world2.cells[index].coordinates << endl;
        }
    }

    // create new paths
    Graph graph = world2.create_graph();
    Paths paths(graph);
    auto new_path = paths.get_astar(graph);

    new_path.save("../../cellworld_data/paths/hexagonal." + occlusions_name  + ".astar.robot");
    cg2.occluded_cells().save("../../cellworld_data/cell_group/hexagonal." + occlusions_name + ".occlusions.robot");

    cout << "done....." << endl;




    return 0;
}

