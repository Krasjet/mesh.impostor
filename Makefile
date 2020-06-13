ifndef OF_ROOT
	OF_ROOT=$(realpath ../../..)
endif

include $(OF_ROOT)/libs/openFrameworksCompiled/project/makefileCommon/compile.project.mk

.DEFAULT_GOAL := Release

run: Release

