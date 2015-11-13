#include "mpdd-helper.h"
#include "dce-application.h"
#include "ns3/log.h"
#include "utils.h"
#include <fstream>
#include <stdlib.h>
#include <unistd.h>

NS_LOG_COMPONENT_DEFINE ("MpddHelper");

namespace ns3 {

MpddHelper::MpddHelper ()
{
}

ApplicationContainer
MpddHelper::Install (NodeContainer c, int copy, std::string id)
{
    std::stringstream oss;

    if(copy == 1){
      NS_LOG_FUNCTION (this);
      ApplicationContainer apps;
      for (NodeContainer::Iterator j = c.Begin (); j != c.End (); ++j){
          int nodeId = (*j)->GetId ();
          std::stringstream oss;
          oss << "files-" << nodeId << "/var/run";
          UtilsEnsureDirectoryExists (oss.str ());
          oss.str(std::string());

          oss << "files-" << nodeId;
          UtilsEnsureDirectoryExists (oss.str ());

          oss << "/etc/";
          UtilsEnsureDirectoryExists (oss.str ());

          oss << "mpd";
          UtilsEnsureDirectoryExists (oss.str ());
          std::vector <std::pair <std::string, std::string> >::iterator iter;

          for (iter = m_files.begin (); iter != m_files.end (); ++iter){
              CopyRealFileToVirtual (nodeId, (*iter).first, (*iter).second);
          }
      }
      return DceApplicationHelper::Install (c);
  } else if(copy == 0){
        for(NodeContainer::Iterator j = c.Begin (); j != c.End (); ++j){
          int nodeId = (*j)->GetId ();
          std::stringstream oss;
          std::stringstream outFile;
          oss << "files-" << nodeId << "/var/run";
          UtilsEnsureDirectoryExists (oss.str ());
          oss.str(std::string());
          outFile << "files-" << nodeId;
          UtilsEnsureDirectoryExists(outFile.str());

          outFile << "/etc/";
          UtilsEnsureDirectoryExists(outFile.str());

          outFile << "mpd/";
          UtilsEnsureDirectoryExists(outFile.str());
          outFile << "mpdd.conf";
          oss << "version = \"0.10\";" << std::endl;
          oss << "host_id = \"" << id << "-" << nodeId << "\";" << std::endl;
          oss << "application:" << std::endl;
          oss << "{" << std::endl;
          oss << "\thost = true;" << std::endl;
          if(dissList.size() > 0){
            oss << "\tdissemination = [" << std::endl;
            for(int i = 0; i < dissList.size(); i++){
              if(i == dissList.size()-1){
                oss << "\t\t\"" << dissList.at(i) <<  "\"" << std::endl;
              } else {
                oss << "\t\t\"" << dissList.at(i) <<  "\"," << std::endl;
              }
            }
            oss << "\t];\n" << std::endl;
          }
          if(ignoreList.size() > 0){
            oss << "\tignore = [" << std::endl;
            for(int i = 0; i < ignoreList.size(); i++){
              if(i == ignoreList.size()-1){
                oss << "\t\t\"" << ignoreList.at(i) <<  "\"" << std::endl;
              } else {
                oss << "\t\t\"" << ignoreList.at(i) <<  "\"," << std::endl;
              }
            }
            oss << "\t];\n" << std::endl;
          }
          oss << "};" << std::endl;

          WriteStrToVirtualFile(nodeId, oss.str(), outFile.str());
        };
      return DceApplicationHelper::Install (c);
  } else {
    for(NodeContainer::Iterator j = c.Begin (); j != c.End (); ++j){
      int nodeId = (*j)->GetId ();
      std::stringstream oss;
      std::stringstream outFile;
      oss << "files-" << nodeId << "/var/run";
      UtilsEnsureDirectoryExists (oss.str ());
      oss.str(std::string());

      outFile << "files-" << nodeId;
      UtilsEnsureDirectoryExists(outFile.str());

      outFile << "/etc/";
      UtilsEnsureDirectoryExists(outFile.str());

      outFile << "mpd/";
      UtilsEnsureDirectoryExists(outFile.str());
      outFile << "mpdd.conf";
      oss << id << "-" << nodeId << std::endl;
      if(dissList.size() > 0){
        for(int i = 0; i < dissList.size(); i++){
          if(i == dissList.size()-1){
            oss << dissList.at(i) << std::endl;
          } else {
            oss << dissList.at(i) <<  ",";
          }
        }
      }
      if(ignoreList.size() > 0){
        for(int i = 0; i < ignoreList.size(); i++){
          if(i == ignoreList.size()-1){
            oss <<  ignoreList.at(i) << std::endl;
          } else {
            oss <<  ignoreList.at(i) << ",";
          }
        }
      }

      WriteStrToVirtualFile(nodeId, oss.str(), outFile.str());
    };
    return DceApplicationHelper::Install (c);
  }
}

ApplicationContainer
MpddHelper::InstallInNode (Ptr<Node> node, int copy, std::string id)
{
    int nodeId = node->GetId ();


    if(copy == 1){
        NS_LOG_FUNCTION (this);
        ApplicationContainer apps;
        std::stringstream oss;
        oss << "files-" << nodeId << "/var/run";
        UtilsEnsureDirectoryExists (oss.str ());
        oss.str(std::string());

        oss << "files-" << nodeId;
        UtilsEnsureDirectoryExists (oss.str ());

        oss << "/etc/";
        UtilsEnsureDirectoryExists (oss.str ());

        oss << "mpd";
        UtilsEnsureDirectoryExists (oss.str ());
        std::vector <std::pair <std::string, std::string> >::iterator iter;

        for (iter = m_files.begin (); iter != m_files.end (); ++iter){
            CopyRealFileToVirtual (nodeId, (*iter).first, (*iter).second);
        }
        return DceApplicationHelper::Install (node);
    } else if(copy == 0){
        std::stringstream oss;
        std::stringstream outFile;
        oss << "files-" << nodeId << "/var/run";
        UtilsEnsureDirectoryExists (oss.str ());
        oss.str(std::string());
        outFile << "files-" << nodeId;
        UtilsEnsureDirectoryExists(outFile.str());

        outFile << "/etc/";
        UtilsEnsureDirectoryExists(outFile.str());

        outFile << "mpd/";
        UtilsEnsureDirectoryExists(outFile.str());
        outFile << "mpdd.conf";
        oss << "version = \"0.10\";" << std::endl;
        oss << "host_id = \"" << id << "-" << nodeId << "\";" << std::endl;
        oss << "application:" << std::endl;
        oss << "{" << std::endl;
        oss << "\thost = true;" << std::endl;
        if(dissList.size() > 0){
            oss << "\tdissemination = [" << std::endl;
            for(int i = 0; i < dissList.size(); i++){
                if(i == dissList.size()-1){
                    oss << "\t\t\"" << dissList.at(i) <<  "\"" << std::endl;
                } else {
                    oss << "\t\t\"" << dissList.at(i) <<  "\"," << std::endl;
                }
            }
            oss << "\t];\n" << std::endl;
        }
        if(ignoreList.size() > 0){
            oss << "\tignore = [" << std::endl;
            for(int i = 0; i < ignoreList.size(); i++){
                if(i == ignoreList.size()-1){
                    oss << "\t\t\"" << ignoreList.at(i) <<  "\"" << std::endl;
                } else {
                    oss << "\t\t\"" << ignoreList.at(i) <<  "\"," << std::endl;
                }
            }
            oss << "\t];\n" << std::endl;
        }
        oss << "};" << std::endl;

        WriteStrToVirtualFile(nodeId, oss.str(), outFile.str());
        return DceApplicationHelper::Install (node);
    } else {
        std::cout << "Creating mpdd.conf\n";
        std::stringstream oss;
        std::stringstream outFile;

        oss << "files-" << nodeId << "/var/run";
        UtilsEnsureDirectoryExists (oss.str ());
        oss.str(std::string());

        outFile << "files-" << nodeId;
        UtilsEnsureDirectoryExists(outFile.str());

        outFile << "/etc/";
        UtilsEnsureDirectoryExists(outFile.str());

        outFile << "mpd/";
        UtilsEnsureDirectoryExists(outFile.str());
        outFile << "mpdd.conf";
        oss << id << "-" << nodeId << std::endl;
        if(dissList.size() > 0){
            for(int i = 0; i < dissList.size(); i++){
                if(i == dissList.size()-1){
                    oss << dissList.at(i) << std::endl;
                } else {
                    oss << dissList.at(i) <<  ",";
                }
            }
        }
        if(ignoreList.size() > 0){
            for(int i = 0; i < ignoreList.size(); i++){
                if(i == ignoreList.size()-1){
                    oss <<  ignoreList.at(i) << std::endl;
                } else {
                    oss <<  ignoreList.at(i) << ",";
                }
            }
        }

        WriteStrToVirtualFile(nodeId, oss.str(), outFile.str());

        return DceApplicationHelper::Install (node);
    }
}


void
MpddHelper::CopyFile (std::string from, std::string to)
{
    std::ifstream f1 (from.c_str (), std::fstream::binary);
    std::ofstream f2 (to.c_str (), std::fstream::trunc | std::fstream::binary);
    f2 << f1.rdbuf ();
    f2.close ();
    f1.close ();
}

void
MpddHelper::IgnoreInterface(std::string ignore)
{
  ignoreList.push_back (std::string(ignore));
}

void
MpddHelper::DisseminationInterface(std::string diss)
{
  dissList.push_back (std::string(diss));
}

void
MpddHelper::AddFile (std::string from, std::string to)
{
    m_files.push_back (std::make_pair (from, to));
}

void
MpddHelper::WriteStrToVirtualFile (int nodeId, std::string content, std::string to)
{
    std::stringstream oss;

    std::string vto = oss.str ();

    size_t pos = vto.find_last_of ("/");
    if (pos != std::string::npos){
        std::string dir = vto.substr (0,pos);
        UtilsEnsureAllDirectoriesExist (vto);
    }

    std::ofstream outFile (to.c_str (), std::fstream::trunc | std::fstream::binary);
    outFile << content;
    outFile.close();
}

void
MpddHelper::CopyRealFileToVirtual (int nodeId, std::string from, std::string to)
{
    std::stringstream oss;

    oss << "files-" << nodeId << to;

    std::string vto = oss.str ();

    size_t pos = vto.find_last_of ("/");
    if (pos != std::string::npos){
        std::string dir = vto.substr (0,pos);
        UtilsEnsureAllDirectoriesExist (vto);
    }
    CopyFile (from, vto);
}


/**
 * Reset environmental variables for the main binary for this application.
 */
void
MpddHelper::ResetEnvironment (void)
{
    m_files.clear();
    ignoreList.clear();
    dissList.clear();
    DceApplicationHelper::ResetEnvironment();
}

}
