#include "signals.h"
#include <verilated.h>
#include <sys/stat.h>
#include <string>

// Include model header, generated from Verilating "top.v"
#include "Vlzc.h"

// If "verilator --trace" is used, include the tracing class
//#if VM_TRACE

#include <verilated_fst_c.h>
VerilatedFstC* tfp;

//#endif

// // Current simulation time (64-bit unsigned)
 vluint64_t main_time = 0;
// // Called by $time in Verilog
 double sc_time_stamp() {
     return main_time;  // Note does conversion to real, to match SystemC
 }
//

union WideSignal {
  uint32_t* sig32;
  uint64_t* sig64;
  };


Vlzc* top;
void signals::init_top(std::string name) {

  //Verilated::debug(0);
  // Set debug level, 0 is off, 9 is highest presently used
  Verilated::debug(0);
  // Randomization reset policy
  Verilated::randReset(2);

  // Construct the Verilated model, from Vtop.h generated from Verilating "top.v"
  top = new Vlzc; // Or use a const unique_ptr, or the VL_UNIQUE_PTR wrapper

  //#if VM_TRACE
  // If verilator was invoked with --trace argument,
  // and if at run time passed the +trace argument, turn on tracing
  tfp = NULL;
  //  const char* flag = Verilated::commandArgsPlusMatch("trace");
  //  if (flag && 0==strcmp(flag, "+trace")) {
    Verilated::traceEverOn(true);  // Verilator must compute traced signals
    //VL_PRINTF("Enabling waves into logs/vlt_dump.vcd...\n");

    tfp = new VerilatedFstC;

    top->trace(tfp, 99);  // Trace 99 levels of hierarchy
    Verilated::mkdir("logs");

    //mkdir("logs",0x775);

	std::string f = "logs/" + name + ".fst";

       tfp->open(f.c_str());

    //  }
  //#endif

  // Set some inputs
}

  
      
	
uint32_t signals::clk(uint32_t val) {
  top->clk = val;
  return top->clk;
}
	
      
  
      
	
uint32_t signals::lzc_cnt() {
  return top->lzc_cnt;
}
	
      
  
      
	
uint32_t signals::temp() {
  return top->temp;
}
	
      
  
      
	
uint32_t signals::i_data(uint32_t val) {
  top->i_data = val;
  return top->i_data;
}
	
      
  


int signals::eval() {
  main_time++;
  top->eval();
  tfp->dump(main_time);
  // Read outputs
  /*  VL_PRINTF ("[%" VL_PRI64 "d] clk=%x rstl=%x iquad=%" VL_PRI64 "x"
	     " -> oquad=%" VL_PRI64"x owide=%x_%08x_%08x\n",
	     main_time, top->clk, top->reset_l, top->in_quad,
	     top->out_quad, top->out_wide[2], top->out_wide[1], top->out_wide[0]);*/
  return 0;
}

int signals::finish() {
  top->final();
  tfp->close();
  tfp = NULL;
  return 0;
}


    
      
Napi::Number signals::clkWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if(info.Length() > 1 || (info.Length() == 1 && !info[0].IsNumber())) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }
    
  Napi::Number returnValue;
  if(info.Length() == 1) {
    Napi::Number val = info[0].As<Napi::Number>();
    returnValue = Napi::Number::New(env, signals::clk(val.Int32Value()));
  } else {
    returnValue = Napi::Number::New(env, top->clk);
  }
  return returnValue;
}
      
    

    
      
Napi::Number signals::lzc_cntWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if(info.Length() > 0) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }
    
  Napi::Number returnValue;
  returnValue = Napi::Number::New(env, top->lzc_cnt);
  return returnValue;
}
      
    

    
      
Napi::Number signals::tempWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if(info.Length() > 0) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }
    
  Napi::Number returnValue;
  returnValue = Napi::Number::New(env, top->temp);
  return returnValue;
}
      
    

    
      
Napi::Number signals::i_dataWrapped(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  if(info.Length() > 1 || (info.Length() == 1 && !info[0].IsNumber())) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }
    
  Napi::Number returnValue;
  if(info.Length() == 1) {
    Napi::Number val = info[0].As<Napi::Number>();
    returnValue = Napi::Number::New(env, signals::i_data(val.Int32Value()));
  } else {
    returnValue = Napi::Number::New(env, top->i_data);
  }
  return returnValue;
}
      
    




void signals::evalWrapped(const Napi::CallbackInfo& info) {
    signals::eval();
  // Napi::Env env = info.Env();

  // Napi::Number returnValue = Napi::Number::New(env, signals::eval());
  // return returnValue;
  
}

void signals::finishWrapped(const Napi::CallbackInfo& info) {
    signals::finish();
    // Napi::Env env = info.Env();

    // Napi::Number returnValue = Napi::Number::New(env, signals::finish());
    // return returnValue;
}

void signals::initWrapped(const Napi::CallbackInfo& info) {
    std::string name = "waveform";
    Napi::Env env = info.Env();
    if(info.Length() > 0 ) {
	if(!info[0].IsString()) {
	    Napi::TypeError::New(env, "String expected").ThrowAsJavaScriptException();
	}
	Napi::String val = info[0].As<Napi::String>();
	name = val.Utf8Value();
    }
    signals::init_top(name);
}

Napi::Object signals::Init(Napi::Env env, Napi::Object exports) {



  exports.Set("clk", Napi::Function::New(env, signals::clkWrapped));



  exports.Set("lzc_cnt", Napi::Function::New(env, signals::lzc_cntWrapped));



  exports.Set("temp", Napi::Function::New(env, signals::tempWrapped));



  exports.Set("i_data", Napi::Function::New(env, signals::i_dataWrapped));


  exports.Set("eval", Napi::Function::New(env, signals::evalWrapped));
  exports.Set("finish", Napi::Function::New(env, signals::finishWrapped));
  exports.Set("init", Napi::Function::New(env, signals::initWrapped));
  return exports;

}
