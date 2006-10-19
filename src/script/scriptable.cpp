//+----------------------------------------------------------------------------+
//| Description:  Magic Set Editor - Program to make Magic (tm) cards          |
//| Copyright:    (C) 2001 - 2006 Twan van Laarhoven                           |
//| License:      GNU General Public License 2 or later (see file COPYING)     |
//+----------------------------------------------------------------------------+

// ----------------------------------------------------------------------------- : Includes

#include <script/scriptable.hpp>
#include <script/context.hpp>
#include <script/parser.hpp>
#include <script/script.hpp>
#include <script/value.hpp>

// ----------------------------------------------------------------------------- : Store

void store(const ScriptValueP& val, String& var)              { var = static_cast<String>(*val); }
void store(const ScriptValueP& val, int&    var)              { var = *val; }
void store(const ScriptValueP& val, double& var)              { var = *val; }
void store(const ScriptValueP& val, bool&   var)              { var = static_cast<int>(*val); }
void store(const ScriptValueP& val, Defaultable<String>& var) { var.assign(*val); }

// ----------------------------------------------------------------------------- : OptionalScript

OptionalScript::~OptionalScript() {}

ScriptValueP OptionalScript::invoke(Context& ctx) const {
	if (script) {
		return ctx.eval(*script);
	} else {
		return script_nil;
	}
}

// custom reflection, different for each type

template <> void Reader::handle(OptionalScript& os) {
	handle(os.unparsed);
	// read the script
	os.script = parse(os.unparsed);
}

template <> void Writer::handle(const OptionalScript& os) {
	handle(os.unparsed);
}

template <> void GetDefaultMember::handle(const OptionalScript& os) {
	// reflect as the script itself
	if (os.script) {
		handle(os.script);
	} else {
		handle(script_nil);
	}
}