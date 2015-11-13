#ifndef MPDD_HELPER_H
#define MPDD_HELPER_H
#include "dce-application-helper.h"
#include <fstream>
#include <vector>


namespace ns3 {

class MpddHelper : public DceApplicationHelper
{
    public:
        MpddHelper ();
        virtual ApplicationContainer Install (NodeContainer c, int copy, std::string id);
        virtual ApplicationContainer InstallInNode (Ptr<Node> node, int copy, std::string id);
        void AddFile (std::string from, std::string to);
        void IgnoreInterface(std::string ignore);
        void DisseminationInterface(std::string diss);
        /**
        * Reset environmental variables for the main binary for this application.
        */
        void ResetEnvironment (void);

    private:
        void CopyFile (std::string from, std::string to);
        std::vector<std::pair <std::string, std::string> > m_files;
        std::vector<std::string > ignoreList;
        std::vector<std::string > dissList;
        void CopyRealFileToVirtual (int nodeId, std::string from, std::string to);
        void WriteStrToVirtualFile (int nodeId, std::string content, std::string to);
    };
}
#endif // MPDD_HELPER_H
