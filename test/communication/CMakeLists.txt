# Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

if(NOT ((MSVC OR MSVC_IDE) AND EPROSIMA_INSTALLER) AND fastcdr_FOUND)
    find_package(PythonInterp 3)

    ###############################################################################
    # Binaries
    ###############################################################################
    set(COMMON_SOURCE ${PROJECT_SOURCE_DIR}/test/blackbox/types/HelloWorld.cpp
        ${PROJECT_SOURCE_DIR}/test/blackbox/types/HelloWorldType.cpp
        )

    set(PUBLISHER_SOURCE ${COMMON_SOURCE}
        Publisher.cpp
        )
    add_executable(SimpleCommunicationPublisher ${PUBLISHER_SOURCE})
    target_include_directories(SimpleCommunicationPublisher PRIVATE ${PROJECT_SOURCE_DIR}/test/blackbox)
    target_link_libraries(SimpleCommunicationPublisher fastrtps fastcdr)

    set(SUBSCRIBER_SOURCE ${COMMON_SOURCE}
        Subscriber.cpp
        )
    add_executable(SimpleCommunicationSubscriber ${SUBSCRIBER_SOURCE})
    target_include_directories(SimpleCommunicationSubscriber PRIVATE ${PROJECT_SOURCE_DIR}/test/blackbox)
    target_link_libraries(SimpleCommunicationSubscriber fastrtps fastcdr)

    if(PYTHONINTERP_FOUND)
        add_test(NAME SimpleCommunication
            COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/simple_communication.py)

        # Set test with label NoMemoryCheck
        set_property(TEST SimpleCommunication PROPERTY LABELS "NoMemoryCheck")

        set_property(TEST SimpleCommunication PROPERTY ENVIRONMENT
            "SIMPLE_COMMUNICATION_PUBLISHER_BIN=$<TARGET_FILE:SimpleCommunicationPublisher>")
        set_property(TEST SimpleCommunication APPEND PROPERTY ENVIRONMENT
            "SIMPLE_COMMUNICATION_SUBSCRIBER_BIN=$<TARGET_FILE:SimpleCommunicationSubscriber>")
        if(WIN32)
            string(REPLACE ";" "\\;" WIN_PATH "$ENV{PATH}")
            set_property(TEST SimpleCommunication APPEND PROPERTY ENVIRONMENT
                "PATH=$<TARGET_FILE_DIR:${PROJECT_NAME}>\\;$<TARGET_FILE_DIR:fastcdr>\\;${WIN_PATH}")
        endif()

        add_test(NAME LivelinessAssertion
            COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/liveliness_assertion.py)

        # Set test with label NoMemoryCheck
        set_property(TEST LivelinessAssertion PROPERTY LABELS "NoMemoryCheck")

        set_property(TEST LivelinessAssertion PROPERTY ENVIRONMENT
            "SIMPLE_COMMUNICATION_PUBLISHER_BIN=$<TARGET_FILE:SimpleCommunicationPublisher>")
        set_property(TEST LivelinessAssertion APPEND PROPERTY ENVIRONMENT
            "SIMPLE_COMMUNICATION_SUBSCRIBER_BIN=$<TARGET_FILE:SimpleCommunicationSubscriber>")
        if(WIN32)
            string(REPLACE ";" "\\;" WIN_PATH "$ENV{PATH}")
            set_property(TEST LivelinessAssertion APPEND PROPERTY ENVIRONMENT
                "PATH=$<TARGET_FILE_DIR:${PROJECT_NAME}>\\;$<TARGET_FILE_DIR:fastcdr>\\;${WIN_PATH}")
        endif()
    endif()
endif()
