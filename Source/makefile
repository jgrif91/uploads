# Capture the current directory of the make file
# =====================================================
DIR := ${CURDIR}

# Compiler and Compiler Args (default)
# =====================================================
compiler := cc
compilerArg := -std=gnu11 -o

# Shared files
# =====================================================
shDir := $(DIR)/Shared
shComFun := $(shDir)/CommonFunctions.c
shComFunH := $(shDir)/CommonFunctions.h
shMyUNP := $(shDir)/myunp.h

# Server files
# =====================================================
svOutput := server.binary
svDir := $(DIR)/Server
svDriver := $(svDir)/Driver.c
svChildServer := $(svDir)/ChildServer.c
svProgInfo := $(svDir)/ProgInformation.c
svGameLL := $(svDir)/GameLinkedList.c
svCustomerLL := $(svDir)/CustomerLinkedList.c
svWelcome := $(svDir)/Welcome.c
svMainMenu := $(svDir)/MainMenu.c
svUpdateUsrInfo := $(svDir)/UpdateUserAccount.c
svSigChldPID := $(svDir)/sigchldwaitpid.c

# Client files
# =====================================================
clOutput := client.binary
clDir := $(DIR)/Client
clDriver := $(clDir)/Driver.c
clComm := $(clDir)/Comm.c

# Main Make Operation
# =====================================================
ALL: server client
server:
	@echo Compiling Server Build. . .
	$(compiler) $(compilerArg) $(svOutput) -I $(shDir) -I $(svDir) $(shComFun) $(svProgInfo) $(svGameLL) $(svCustomerLL) $(svWelcome) $(svMainMenu) $(svUpdateUsrInfo) $(svSigChldPID) $(svChildServer) $(svDriver)
	@echo Successfully Compiled Build!
client:
	@echo Compiling Client Build. . .
	@$(compiler) $(compilerArg) $(clOutput) -I $(shDir) -I $(clDir) $(shComFun) $(clComm) $(clDriver)
	@echo Successfully Compiled Build!
clean:
	@echo Thrashing Compiled Builds. . .
	@rm $(svOutput) $(clOutput)
	@echo Successfully Expunged Binary Builds!
