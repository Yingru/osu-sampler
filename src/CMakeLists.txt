add_executable(${PROJECT_NAME}
  arsenal.cpp
  emissionfunction.cpp
  main.cpp
  NBD.cpp
  ParameterReader.cpp
  Poisson.cpp
  RandomVariable.cpp
  RandomVariable1DArray.cpp
  RandomVariable2DArray.cpp
  readindata.cpp
  Table.cpp
  TableFunction.cpp
)

install(TARGETS ${PROJECT_NAME} DESTINATION ${PROJECT_NAME})
