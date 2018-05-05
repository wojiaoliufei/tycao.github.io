#include "manager.h"
#include "trim.h"

SybaseManager::SybaseManager(std::string hosts, std::string userName, std::string password, std::string dbName, unsigned int port)    
{    
        IsConnected = false;    
        this ->setHosts(hosts);    
        this ->setUserName(userName);    
        this ->setPassword(password);    
        this ->setDBName(dbName);    
        this ->setPort(port);    
}    

SybaseManager::~SybaseManager()    
{    
        destroyConnection();    
}    

void SybaseManager::setDBName(string dbName)    
{    
        if ( dbName.empty() )    
        {    
                std::cout << "DBName is null! Used default value: master" << std::endl;    
                this ->DBNAME = new char[5];    
                strcpy(this ->DBNAME, "master");    
        }    
        else    
        {    
                this ->DBNAME = new char[dbName.length()];    
                strcpy(this ->DBNAME, dbName.c_str());    
        }    
}    

void SybaseManager::setHosts(string hosts)    
{    
        if ( hosts.empty() )    
        {    
                std::cout << "Hosts is null! Used default value: localhost" << std::endl;    
                this ->HOSTS = new char[9];    
                strcpy(this ->HOSTS, "localhost");    
        }    
        else    
        {    
                this ->HOSTS = new char[hosts.length()];    
                strcpy(this ->HOSTS, hosts.c_str());    
        }    
}    

void SybaseManager::setPassword(string password)    
{    
        if ( password.empty() )    
        {    
                std::cout << "Password is null! Used default value: " << std::endl;    
                this ->PASSWORD = new char[1];    
                strcpy(this ->PASSWORD, "");    
        }    
        else    
        {    
                this ->PASSWORD = new char[password.length()];    
                strcpy(this ->PASSWORD, password.c_str());    
        }    
}    

void SybaseManager::setPort(unsigned int port)    
{    
        if ( !port )    
        {    
                std::cout << "Port number is null! Used default value: 0" << std::endl;    
                this ->DEFAULTPORT = 0;    
        }    
        else    
        {    
                this ->DEFAULTPORT = port;    
        }    
}    

void SybaseManager::setUserName(string userName)    
{    
        if ( userName.empty() )    
        {    
                std::cout << "UserName is null! Used default value: sa" << std::endl;    
                this ->USERNAME = new char[4];    
                strcpy(this ->USERNAME, "sa");    
        }    
        else    
        {    
                this ->USERNAME = new char[userName.length()];    
                strcpy(this ->USERNAME, userName.c_str());    
        }    
}    

void SybaseManager::initConnection()    
{    
        string Charset = "UTF-8";    
        dbinit();    
        LOGINREC *loginREC = dblogin();    
        DBSETLUSER(loginREC, this ->USERNAME);    
        DBSETLPWD(loginREC, this ->PASSWORD);    
        DBSETLCHARSET(loginREC, Charset.c_str());    
        dbProcess = dbopen(loginREC, this ->HOSTS);    
        if ( dbProcess == FAIL )    
        {    
                std::cout << "Connect to SQL Server failed!" << std::endl;    
        }    
        if ( dbuse( dbProcess, this ->DBNAME ) == FAIL )    
        {    
                std::cout << "Use table failed!" << std::endl;    
        }    
}    

bool SybaseManager::runSQLCommand( string sql )    
{    
        dbcmd(dbProcess, sql.c_str());    
        if ( dbsqlexec(dbProcess) == FAIL )    
        {    
                std::cout << "Query from database failed!" << std::endl;    
        }    
        DBINT result_code;    
        vector<string> objectValue;    


        while ( (result_code = dbresults(dbProcess)) != NO_MORE_RESULTS )    
        {    
                struct Column    
                {    
                        char* colName;    
                        char* colBuffer;    
                        int colType, colSize, colStatus;    
                } *columns, *pCol;    
                int nColumns;    
                int rowNo;    
                if ( result_code == SUCCEED )    
                {    
                        nColumns = dbnumcols(dbProcess);    
                        if ( (columns = (Column*)calloc(nColumns, sizeof(struct Column))) == NULL )    
                        {    
                                std::cout << "Error at bind data" << std::endl;    
                                return false;    
                        }    
                        for ( pCol = columns; pCol - columns < nColumns; pCol++ )    
                        {    
                                int colNo = pCol - columns + 1;    
                                pCol ->colName = dbcolname(dbProcess, colNo);    
                                pCol ->colType = dbcoltype(dbProcess, colNo);    
                                pCol ->colSize = dbcollen(dbProcess, colNo);    
                                if ( SYBCHAR != pCol ->colType )    
                                {    
                                        pCol ->colSize = dbwillconvert(pCol ->colType, SYBCHAR);    
                                }    

                                if ( (pCol ->colBuffer = (char*)calloc(1, pCol ->colSize + 1)) == NULL )    
                                {    
                                        std::cout << "Check column buffer error!" << std::endl;    
                                        return false;    
                                }    

                                if ( dbbind(dbProcess, colNo, STRINGBIND, pCol ->colSize + 1, (BYTE*)pCol ->colBuffer) == FAIL )    
                                {    
                                        std::cout << "Running dbbind() error!" << std::endl;    
                                        return false;    
                                }    

                                if ( dbnullbind(dbProcess, colNo, &pCol ->colStatus) == FAIL )    
                                {    
                                        std::cout << "Running dbnullbind() error!" << std::endl;    
                                        return false;    
                                }    
                        }    

                        while ( (rowNo = dbnextrow(dbProcess)) != NO_MORE_ROWS )    
                        {    
                                objectValue.clear();    
                                switch ( rowNo )    
                                {    
                                case REG_ROW:    
                                        for ( pCol = columns; pCol - columns < nColumns; pCol++ )    
                                        {    
                                                const char* columnBuffer = pCol ->colStatus == -1 ? "NULL" : pCol ->colBuffer;    
                                                objectValue.push_back(trim(columnBuffer));        //        std::cout << columnBuffer << std::endl;    
                                        }    
                                        break;    
                                case BUF_FULL:    
                                        assert( rowNo != BUF_FULL );    
                                        break;    
                                case FAIL:    
                                        std::cout << "Get result error!" << std::endl;    
                                        break;    
                                default:    
                                        std::cout << "Get result ignore, row number:" << rowNo << std::endl;    
                                }    
                                this ->resultList.push_back(objectValue);    
                        }    
                        for ( pCol = columns; pCol - columns < nColumns; pCol++ )    
                        {    
                                free( pCol ->colBuffer );    
                        }    
                        free( columns );    
                        /*    
                        if ( DBCOUNT(dbProcess) > -1 )    
                        {    
                                std::cout << "Affected rows:" << DBCOUNT(dbProcess) << std::endl;    
                        }    
                        */    
                        if ( dbhasretstat(dbProcess) == TRUE )    
                        {    
                                std::cout << "Procedure returned " << dbhasretstat(dbProcess) << std::endl;    
                        }    
                }    
        }    
        return true;    
}    

void SybaseManager::destroyConnection()    
{    
        dbclose(dbProcess);    
}    

bool SybaseManager::getConnectionStatus()    
{    
        return IsConnected;    
}    

vector< vector<string> > SybaseManager::getResult()    
{    
        return this ->resultList;    
} 
