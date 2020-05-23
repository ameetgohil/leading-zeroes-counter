#include "napi.h"
#include <string>

namespace signals {

    void init_top(std::string name);
  
  int tick();
  
      
	
  uint32_t clk(uint32_t val);
	
      
  
      
	
  uint32_t lzc_cnt();
	
      
  
      
	
  uint32_t temp();
	
      
  
      
	
  uint32_t i_data(uint32_t val);
	
      
  
  int eval();
  int finish();
  
  Napi::Number TickWrapped(const Napi::CallbackInfo& info);
  
      
  Napi::Number clkWrapped(const Napi::CallbackInfo& info);
      
  
      
  Napi::Number lzc_cntWrapped(const Napi::CallbackInfo& info);
      
  
      
  Napi::Number tempWrapped(const Napi::CallbackInfo& info);
      
  
      
  Napi::Number i_dataWrapped(const Napi::CallbackInfo& info);
      
  
  void evalWrapped(const Napi::CallbackInfo& info);
  void finishWrapped(const Napi::CallbackInfo& info);
  void initWrapped(const Napi::CallbackInfo& info);
  Napi::Object Init(Napi::Env env, Napi::Object exports);
};

