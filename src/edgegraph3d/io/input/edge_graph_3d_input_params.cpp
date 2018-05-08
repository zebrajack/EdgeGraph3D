/*
 ***********************************************************************
 *
 * 							  EdgeGraph3D
 *
 *         Copyright (C) 2018 Andrea Bignoli (andrea.bignoli@gmail.com)
 *                         All rights reserved
 *
 ***********************************************************************
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 *
*/


#include "edge_graph_3d_input_params.hpp"

#include <getopt.h>
#include <cstring>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

void read_line_in_char_array(std::ifstream &is, char* &param) {
	std::string sparam;
	std::getline(is, sparam);
	param = new char[sparam.length() + 1];
	std::strcpy(param, sparam.c_str());
}

void read_line_in_int(std::ifstream &is, unsigned long &param) {
	std::string sparam;
	std::getline(is, sparam);
	param = stoi(sparam);
}

void usage(int argc, char *argv[]) {
	cout << "\n\nEdgeGraph3D\n===========\n\nUnrecognized input parameters. \n\nCall format:\n\n\t"<<argv[0]<<" [-i] images/ edges/ working_folder/ input_sfm_data.json output.json\n\n";
	cout << "\t images/ : folder containing input images" << endl;
	cout << "\t edges/ : folder containing input edge images with black background and white edges" << endl;
	cout << "\t working_folder/ : working folder, will be used by EdgeGraph3D to output files" << endl;
	cout << "\t input_sfm_data.json : input structure from motion data in JSON format" << endl;
	cout << "\t output.json : output structure from motion data in JSON format, integrating the input structure from motion data with sampled edge-points" << endl;
	cout << endl << "Optional arguments:" << endl << endl;
	cout << "\t -i : output debug images" << endl << endl;
}

bool read_edge_matcher_input_params(int argc, char *argv[], edge_matcher_input_params &emip) {
	/*
	 * ++ Parameters ++
	 *
	 * - images_folder : folder containing input images
	 * - input_edges_folder : folder containing input edge images w/ black background and white edges
	 * - em_out_folder : working folder, will be used by the 3D edge reconstruction pipeline to output files
	 * - sfm_data_file.json : input structure from motion data, in OpenMVG format
	 * - output.json : output JSON file, in OpenMVG format, integrating the input file with edge-points sampled on edges generated by EdgeGraph3D
	 *
	 * ++ Optional parameters
	 *
	 * - [-i] : output debug images, i.e., 2D-to-2D polyline matching, edge-point reprojections
	 *
	 * ++ Call format
	 *
	 * 		edgeRec [-i] images/ edge_images/ working_folder/ input_sfm_data.json output.json
	 *
	 */

	emip.original_refpoints = 0;
	emip.input_plg_folder = ""; // will be integrated
	emip.real_camera_poses_file = NULL;
	emip.output_debug_images = false;

  static const char *opt_string = "i";
  int opt = getopt(argc, argv, opt_string);
  while (opt != -1) {
    switch (opt) {

    case 'i': emip.output_debug_images = true; break;

    default:
      cerr << "unknown argument" << endl;
      return false;
    }
    opt = getopt(argc, argv, opt_string);
  }

   if (argc - optind != 5) {
    usage(argc, argv);
    return false;
  } else {
	  emip.images_folder = argv[optind];
	  emip.input_edges_folder = argv[optind+1];
	  emip.em_out_folder = argv[optind+2];
	  emip.sfm_data_file = argv[optind+3];
	  emip.output_json = argv[optind+4];
  }

   emip.real_camera_poses_file_valid = emip.real_camera_poses_file != NULL;

  return true;
}
