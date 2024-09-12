using namespace std;
using namespace ns3;
#include <vector>
#include "UDPStructs.h"
class myContext: public MTContext
{
	public:
		int src_port;
		int dst_port;
		int sent_count;
		int recv_count;
		int MTU;
};
