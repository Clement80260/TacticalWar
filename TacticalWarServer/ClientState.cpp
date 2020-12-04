#include "ClientState.h"



ClientState::ClientState(SOCKET sock)
{
	this->sock = sock;
	this->pseudo = "";
	this->isAdmin = false;
}

ClientState::~ClientState()
{

}
