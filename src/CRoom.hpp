class CRoom
{ 
private:
    std::string m_sName;
    std::string m_sDescription;
    
    std::map<std::string, CRoom*> m_mapOfExists;

public:
    CRoom CRoom(std::string sName, std::string sDescription)

    
