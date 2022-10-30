project(xml_lib)

set(HEADER_FILES 
  Attribute.h
  Comment.h
  Document.h
  Node.h
  ProcessingInstruction.h
  Element.h
  TextElement.h
  XmlDocument.h
  XmlSearcher.h
  exceptions/XmlException.h
  exceptions/ParsingTagException.h
  exceptions/CantFindTagException.h
  exceptions/CantFindAttributeException.h
)

set(SOURCE_FILES 
  Attribute.cpp
  Comment.cpp
  Document.cpp
  Node.cpp
  ProcessingInstruction.cpp
  Element.cpp
  TextElement.cpp
  XmlDocument.cpp
  XmlSearcher.cpp
  exceptions/XmlException.cpp
  exceptions/ParsingTagException.cpp
  exceptions/CantFindTagException.cpp
  exceptions/CantFindAttributeException.cpp
)

# include(exceptions)
# include(src)
# include(utils)

add_library(xml_lib STATIC ${SOURCE_FILES} ${HEADER_FILES}) # ${SOURCE_FILES}