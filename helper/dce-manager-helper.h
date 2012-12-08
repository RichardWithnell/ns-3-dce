#ifndef DCE_MANAGER_HELPER_H
#define DCE_MANAGER_HELPER_H

#include "ns3/object-factory.h"
#include "ns3/attribute.h"
#include "ns3/object-base.h"
#include "ns3/node-container.h"
#include "ns3/nstime.h"
#include <string>

namespace ns3 {

/* Container of information of a DCE finished process */
class ProcStatus
{
public:
  ProcStatus (int n, int e, int p, int64_t ns, int64_t ne, long rs, long re, double nd, long rd, std::string cmd);

  /* node ID */
  int GetNode (void) const;
  /* exit code */
  int GetExitCode (void) const;
  /* Simulated pid */
  int GetPid (void) const;
  /* Start Time in Simulated Time the unit is nanoseconds */
  int64_t GetSimulatedStartTime (void) const;
  /* End Time in Simulated Time the unit is nanoseconds */
  int64_t GetSimulatedEndTime (void) const;
  /* Real Start Time (time_t) */
  long GetRealStartTime (void) const;
  /* Real End Time  */
  long GetRealEndTime (void) const;
  /* Simulated duration in seconds */
  double GetSimulatedDuration (void) const;
  /* real duration in seconds */
  long GetRealDuration (void) const;
  /* Command Line argv[] */
  std::string GetCmdLine (void) const;

private:
   int m_node;
   int m_exitCode;
   int m_pid;
   int64_t m_ns3StartTime;
   int64_t m_ns3EndTime;
   long m_realStartTime;
   long m_realEndTime;
   double m_ns3Duration;
   long m_realDuration;
   std::string m_cmdLine;
};

class DceManagerHelper : public Object
{
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  DceManagerHelper ();
  void SetScheduler (std::string type, 
		     std::string n0 = "", const AttributeValue &v0 = EmptyAttributeValue (),
		     std::string n1 = "", const AttributeValue &v1 = EmptyAttributeValue ());
  void SetDelayModel (std::string type, 
                      std::string n0 = "", const AttributeValue &v0 = EmptyAttributeValue (),
                      std::string n1 = "", const AttributeValue &v1 = EmptyAttributeValue ());
  void SetTaskManagerAttribute (std::string n0, const AttributeValue &v0);
  void SetLoader (std::string type);
  void SetNetworkStack (std::string type,
			std::string n0 = "", const AttributeValue &v0 = EmptyAttributeValue ());
  void SetAttribute (std::string n1, const AttributeValue &v1);
  void Install (NodeContainer nodes);
  // Path used by simulated methods 'execvp' and 'execlp'
  void SetVirtualPath (std::string p);
  std::string GetVirtualPath () const;
  /* Return a Vector of Finished Process */
  static std::vector<ProcStatus> GetProcStatus (void);

private:
  static void RunIp (Ptr<Node> node, Time at, std::string str);
  static void AddAddress (Ptr<Node> node, Time at, std::string name, std::string address);
  void AddRoutes (Ptr<Node> node, std::string r);
  void AddRoute (Ptr<Node> node, std::string r);

  ObjectFactory m_loaderFactory;
  ObjectFactory m_schedulerFactory;
  ObjectFactory m_taskManagerFactory;
  ObjectFactory m_managerFactory;
  ObjectFactory m_networkStackFactory;
  ObjectFactory m_delayFactory;
  std::string m_virtualPath;
};

} // namespace ns3

#endif /* DCE_MANAGER_HELPER_H */
