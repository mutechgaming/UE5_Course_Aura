// Copyrighte Steven Mutek


#include "Player/AuraPlayerState.h"

// netupdatefrequency is how often the server will be updating the clients - 100 is fast, example are games like fortnite

AAuraPlayerState::AAuraPlayerState()
{
	NetUpdateFrequency = 100.f;
}
