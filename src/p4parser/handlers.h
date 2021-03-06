#ifndef _HANDLERS_H
#define _HANDLERS_H

#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>

#include "rapidjson/document.h" //DOM API
#include "rapidjson/prettywriter.h" //stringify JSON
#include "rapidjson/filereadstream.h"

#include "p4parser/p4parser.h"

using namespace rapidjson;
using namespace std;


namespace p4aig
{
	// maps the states in the transitions
	// necessary because, at first pass, all states have not been initialized in structs
	class P4Handler : public BaseReaderHandler<UTF8<>, P4Handler> {
	private:
		// list of the parsers
		list<P4Parser *> parsers;
		// the parser that will be pushed to the list for each iteration
		P4Parser *  curr_parser;
		// the state that will be pushed for this iteration
		State * curr_state;
		// the transition that will be pushed to the list for this iteration
		Transition * curr_transit;
		// the list of the values that the transitions for the curr_state depend on
		// necessary because we want to put them on the transitions, not the states
		// so the transitions are independent
		list<string> transit_value_type;

		//will count the array starts and ends for the overall parser so we know when this
		//entire section is complete
		int arrcount_flag;
		//global variable for whether we are on the "Parsers" portion of the JSON
		//and we should start putting things into structures
		int in_parser_flag;
		// there will be more flags here that turn on as we pass imporant "keys"
		// that mark places where we need to store data
		int name_flag;
		int parse_states_flag;
		int state_flag; //turn off after each transition_key to indicate next state
		int transition_key_flag;
		int value_flag;
		int arr_flag;
		int transitions_flag;
		int next_state_flag;

		// sets all flags equal to 0
		void reset_flags() {
			arrcount_flag = 0;
			in_parser_flag = 0;
			name_flag = 0;
			parse_states_flag = 0;
			state_flag = 0;
			transition_key_flag = 0;
			value_flag = 0;
			arr_flag = 0;
			transitions_flag = 0;
			next_state_flag = 0;
		}

		void second_pass();

	public:
		// constructor
		P4Handler () { reset_flags(); }

		bool Null();
		bool String(const char* str, SizeType length, bool copy);
		bool Key(const char* str, SizeType length, bool copy);
		bool StartArray();
		bool EndArray(SizeType elementCount);

		bool StartObject() { return true; }
		bool EndObject(SizeType memberCount) { return true; }

		bool Bool(bool b) { return true; }
		bool Int(int i) { return true; }
		bool Uint(unsigned u) { return true; }
		bool Int64(int64_t i) { return true; }
		bool Uint64(uint64_t u) { return true; }
		bool Double(double d) { return true; }

		/** setters and getters */
		list<P4Parser *>& get_parsers() { return parsers; }
		list<P4Parser *> copy_parsers() { return parsers; }
	};
}

#endif /* handlers.h */
