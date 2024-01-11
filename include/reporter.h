#pragma once
#include "space.h"
#include "gui_handler.h"
#include "txt_reader.h"
#include "txt_writer.h"
#include "random_reader.h"

class GUI_Handler;

class Reporter {
public:
	Reporter();
	Reporter(const Reporter& other) = delete;
	Reporter(Reporter&& other) noexcept = delete;
	Reporter& operator=(const Reporter& other) = delete;
	Reporter& operator=(Reporter&& other) noexcept = delete;
	~Reporter() = default;

public:
	void random_reader_initialize();
	void txt_reader_initialize();
	void txt_writer_initialize();
	void create_space();
	void read_data(const std::string& filename);
	void run();
	
public:
	std::shared_ptr<Space> space;	
	std::unique_ptr<GUI_Handler> gui_handler;
	std::unique_ptr<Reader> reader;
	std::unique_ptr<Writer> writer;
	bool is_running;	
	bool is_file_writing; 
	bool is_file_reading;
};











