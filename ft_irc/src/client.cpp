#include "../inc/Client.hpp"

Client::Client(int fd) : clientfd(fd), log_in_status(false)
{
}

Client::~Client()
{
}

int Client::getClientfd() const
{
  return clientfd;
}

void Client::setUsername(const std::string &username)
{
  this->username = username;
}

std::string Client::getUsername() const
{
  return username;
}

void Client::setLoginStatus(bool status)
{
  log_in_status = status;
}

bool Client::getLoginStatus() const
{
  return log_in_status;
}

void Client::addGroup(Group *group)
{
  chatgroupList.push_back(group);
}

std::vector<Group *> Client::getGroups() const
{
  return chatgroupList;
}

Group::Group(const std::string &name) : groupName(name), inviteOnly(false), memberLimit(0)
{
}

Group::~Group()
{
}

std::string Group::getGroupName() const
{
  return groupName;
}

void Group::addMember(Client *client)
{
  membersList.push_back(client);
}

void Group::removeMember(Client *client)
{
  membersList.erase(std::remove(membersList.begin(), membersList.end(), client), membersList.end());
}

void Group::addOperator(Client *client)
{
  operatorList.push_back(client);
}

void Group::removeOperator(Client *client)
{
  operatorList.erase(std::remove(operatorList.begin(), operatorList.end(), client), operatorList.end());
}

bool Group::isOperator(Client *client) const
{
  return std::find(operatorList.begin(), operatorList.end(), client) != operatorList.end();
}

void Group::setInviteOnly(bool inviteOnly)
{
  this->inviteOnly = inviteOnly;
}

bool Group::getInviteOnly() const
{
  return inviteOnly;
}

void Group::setPassword(const std::string &password)
{
  this->password = password;
}

std::string Group::getPassword() const
{
  return password;
}

void Group::setMemberLimit(int limit)
{
  memberLimit = limit;
}

int Group::getMemberLimit() const
{
  return memberLimit;
}

void Group::setTopic(const std::string &topic)
{
  this->topic = topic;
}

std::string Group::getTopic() const
{
  return topic;
}