#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"

static const int TestFlags = (
	  EAutomationTestFlags::EditorContext
	| EAutomationTestFlags::CommandletContext
	| EAutomationTestFlags::ClientContext
	| EAutomationTestFlags::ProductFilter );

// Dummy class for example
class ABUIHero
{
public:
	int32 GetGold() const { return 0; }
};

IMPLEMENT_SIMPLE_AUTOMATION_TEST( FBUITestHeroGold, "BUI.Example", TestFlags )
bool FBUITestHeroGold::RunTest( const FString& Parameters )
{
	//ABUIHero* Hero = new ABUIHero();
	//delete Hero;
	return true;
}
//////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST( FBUIHelloWorldTest, "BUI.HelloWorld.Basic", TestFlags )
bool FBUIHelloWorldTest::RunTest( const FString& Parameters )
{
	TestEqual( "Testing that 2+2 == 4", 2 + 2, 4 );
	return true;
}

//////////////////////////////////////////////////////////////////////////

IMPLEMENT_SIMPLE_AUTOMATION_TEST( FBUIHelloWorldLatentTest, "BUI.HelloWorld.Latent", TestFlags )
bool FBUIHelloWorldLatentTest::RunTest( const FString& Parameters )
{
	// Wait for 1.5s, then test
	ADD_LATENT_AUTOMATION_COMMAND( FWaitLatentCommand( 1.5f ) );
	TestEqual( "Testing that 2+2 == 4", 2 + 2, 4 );
	return true;
}

//////////////////////////////////////////////////////////////////////////

// In our example below, we use DEFINE_LATENT_... to defines a class called
// FBUIWaitUntilCountMatches, with two member variables, Start and Target.
// The Update() function is called many times, so we are incrementing the
// member variable Start.
// We return false when the latent command is not complete
DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER( FBUIWaitUntilCountMatches, int32, Start, const int32, Target );
bool FBUIWaitUntilCountMatches::Update()
{
	Start += 1;
	if ( Start < Target )
		return false;
	return true;
}

IMPLEMENT_SIMPLE_AUTOMATION_TEST( FBUICustomLatentTest, "BUI.CustomCommands.Simple", TestFlags )
bool FBUICustomLatentTest::RunTest( const FString& Parameters )
{
	// We are calling the constructor of FBUIWaitUntilCountMatches, and setting
	// its member variables Start and Target ADD_LATENT_AUTOMATION_COMMAND is
	// then adding this instance onto a list of commands to be executed
	ADD_LATENT_AUTOMATION_COMMAND( FBUIWaitUntilCountMatches( 0, 100 ) );
	TestEqual( "Testing that 2+2 == 4", 2 + 2, 4 );
	return true;
}

//////////////////////////////////////////////////////////////////////////
