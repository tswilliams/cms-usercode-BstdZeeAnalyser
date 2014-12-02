{
std::string libLocation = "~/workspace/tswAnaToolsEclipse/lib/libtswAnaTools_CMSSW5XY.so";
//std::string libLocation = "~/Work/BstdZee/tswAnaTools/lib/libtswAnaTools_CMSSW5XY.so"

std::cout << "Loading tswAnaTools lib  (\"" << libLocation << "\")  ...  "; std::cout.flush();
gSystem->Load(libLocation.c_str());
gSystem->Load("libRooFit");
std::cout << "done." << std::endl;
}
