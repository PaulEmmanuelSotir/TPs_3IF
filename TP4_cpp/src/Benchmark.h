/*********************************************************************************
									Benchmark
									---------
*********************************************************************************/

#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <chrono>
#include <iostream>
#include <functional>

#include "Scene.h"

namespace TP4
{
	namespace
	{
		//! Focntion permmetant la mesure du temps d'execution d'une fonction donnée en paramètre.
		//! On assume que la fonction répéte une action élémentaire 'repeat_count' fois.
		void benchmark(const std::string& bench_name, unsigned int repeat_count, std::function<void(void)> benchmark_func);
	}

	//! Execute tous les benchmarks en manipulant une'TP4::Scene'
	inline void execute_benchmarks(TP4::Scene& geometry_scene, unsigned int repetition_count)
	{
		std::cout << "\x1b[33m" << std::endl
			<< R"(  _____ ___ _ _      ___  _     _           ___ ___ _  _  ___ _  _ __  __   _   ___ _  _____ _  _  ___ )" << std::endl
			<< R"( |_   _| _ \ | |    / __|| |_ _| |_   ___  | _ ) __| \| |/ __| || |  \/  | /_\ | _ \ |/ /_ _| \| |/ __|)" << std::endl
			<< R"(   | | |  _/_  _|  | (_|_   _|_   _| |___| | _ \ _|| .` | (__| __ | |\/| |/ _ \|   / ' < | || .` | (_ |)" << std::endl
			<< R"(   |_| |_|   |_|    \___||_|   |_|         |___/___|_|\_|\___|_||_|_|  |_/_/ \_\_|_\_|\_\___|_|\_|\___|)" << std::endl << "\x1b[0m" << std::endl;

		geometry_scene.ClearAll();

		// Creation of 'repetition_count' rectangles
		benchmark("Rectangle creation", repetition_count, [&geometry_scene, repetition_count]()
		{
			static const TP4::Point p1{ 1, 8 };
			static const TP4::Point p2{ 4, 2 };

			unsigned int i = repetition_count + 1;
			while (--i)
				geometry_scene.Add_rectangle("rect" + std::to_string(i), p1, p2);
		});

		geometry_scene.ClearAll();

		// Creation of 'repetition_count' rectangles and undoing them
		benchmark("Rectangle creation with undo", repetition_count, [&geometry_scene, repetition_count]()
		{
			static const TP4::Point p1{ 1, 8 };
			static const TP4::Point p2{ 4, 2 };

			unsigned int i = repetition_count + 1;
			while (--i)
			{
				geometry_scene.Add_rectangle("rect" + std::to_string(i), p1, p2);
				geometry_scene.Undo();
			}
		});

		geometry_scene.ClearAll();

		// Creation of 'repetition_count' rectangles and undoing/redoing them
		benchmark("Rectangle creation with undo/redo", repetition_count, [&geometry_scene, repetition_count]()
		{
			static const TP4::Point p1{ 1, 8 };
			static const TP4::Point p2{ 4, 2 };

			unsigned int i = repetition_count + 1;
			while (--i)
			{
				geometry_scene.Add_rectangle("rect" + std::to_string(i), p1, p2);
				geometry_scene.Undo();
				geometry_scene.Redo();
			}
		});

		geometry_scene.ClearAll();

		// Creation of 'repetition_count' polygons of 4 vertices
		benchmark("Polygon creation", repetition_count, [&geometry_scene, repetition_count]()
		{
			static const std::vector<TP4::Point> vertices{ { 0, 0 },{ 0, 1 },{ 1, 1 },{ 1, 0 } };

			unsigned int i = repetition_count + 1;
			while (--i)
				geometry_scene.Add_polygon("poly" + std::to_string(i), vertices);
		});

		geometry_scene.ClearAll();

		// Creation of 'repetition_count' intersections of rectangles and segments
		benchmark("Intersection creation", repetition_count, [&geometry_scene, repetition_count]()
		{
			static const TP4::Point p1{ 1, 8 };
			static const TP4::Point p2{ 4, 2 };

			unsigned int i = repetition_count + 1;
			while (--i)
			{
				auto i_str = std::to_string(i);
				geometry_scene.Add_segment("seg" + i_str, p1, p2);
				geometry_scene.Add_rectangle("rect" + i_str, p1, p2);
				geometry_scene.Intersect("inter" + i_str, { "seg" + i_str, "rect" + i_str });
			}
		});

		geometry_scene.ClearAll();

		std::cout << std::endl << std::endl << "Press ENTER to continue...";
		std::cin.get();
	}

	namespace
	{
		void benchmark(const std::string& bench_name, unsigned int repeat_count, std::function<void(void)> benchmark_func)
		{
			static unsigned bench_count = 0;

			if (bench_name.empty())
				std::cout << std::endl << std::endl << std::endl << "############# BENCHMARK " << ++bench_count << " #############" << std::endl << std::endl;
			else
				std::cout << std::endl << std::endl << "############# BENCHMARK " << ++bench_count << " (" << bench_name << ") #############" << std::endl;

			auto start = std::chrono::steady_clock::now();

			benchmark_func();

			auto end = std::chrono::steady_clock::now();
			auto diff = end - start;

			std::cout << "Executed benchmark " << repeat_count << " times" << std::endl;
			std::cout << "Total execution time : " << std::chrono::duration<double, std::milli>(diff).count() << " ms" << std::endl;
			std::cout << "Execution mean time : \x1b[32m" << std::chrono::duration<double, std::nano>(diff / repeat_count).count() << " ns \x1b[0m(nano seconds)" << std::endl << std::endl;
			std::cout << "############################################################";
		}
	}
}

#endif // !BENCHMARK_H


