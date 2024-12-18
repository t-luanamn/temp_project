#ifndef CLIENT_HPP
# define CLIENT_HPP

# include <string>
# include <vector>
# include <algorithm>

class Group; // Forward declaration

class Client
{
  public:
    Client(int clientfd);
    ~Client();

    bool isRegistered() const;
    void setRegistered(bool registered);
    int getClientfd() const;
    void setUsername(const std::string &username);
    void setFirstName(const std::string &fname);
    void setLastName(const std::string &lname);
    std::string getUsername() const;
    void setNickname(const std::string &nickname);
    std::string getNickname() const;
    bool isLoggedIn() const;
    void setLoggedIn(bool status);
    std::vector<Group *> getGroups() const;

    // Methods to manage client connection state
    void setNickReceived(bool received);
    void setUserReceived(bool received);
    bool getNickReceived() const;
    bool getUserReceived() const;

  private:
    int _clientfd;
    std::string _username;
    std::string _fname;
    std::string _lname;
    std::string _nick;
    std::vector<Group *> chatgroupList;

    // Member variables to track connection state
    bool _registered;
    bool _nickReceived;
    bool _userReceived;
    bool _loginStatus;
};

class Group
{
  public:
    Group(const std::string &name);
    ~Group();
    std::string getGroupName() const;
    void setGroupName(const std::string &name);
    void addMember(Client *client);
    void removeMember(Client *client);
    void addOperator(Client *client);
    void removeOperator(Client *client);
    bool isOperator(Client *client) const;
    void setOwner(Client *client);
    Client* getOwner() const;
    void setInviteOnly(bool inviteOnly);
    bool getInviteOnly() const;
    void setPassword(const std::string &password);
    std::string getPassword() const;
    void setPasswordOn(bool passwordOn);
    bool getPasswordOn() const;
    void setMemberLimit(int limit);
    int getMemberLimit() const;
    void setMemberLimitOn(bool memberLimitOn);
    bool getMemberLimitOn() const;
    void setTopic(const std::string &topic);
    std::string getTopic() const;
    void setTopicBool(bool topicBool);
    bool getTopicBool() const;
    void addCurrentlySignedIn(Client *client);
    std::vector<Client *> getCurrentlySignedIn() const;
    std::vector<Client *> getMembersList() const;
    std::vector<Client *> getOperatorList() const;

  private:
    std::string groupName;
    std::vector<Client *> membersList;
    std::vector<Client *> operatorList;
    std::vector<Client *> currentlySignedIn;
    bool inviteOnly;
    std::string password;
    bool passwordOn;
    int memberLimit;
    bool memberLimitOn;
    std::string topic;
    bool topicBool;
    Client* owner;
};

#endif