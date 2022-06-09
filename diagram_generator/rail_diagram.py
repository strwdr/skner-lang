import os
from railroad import *

diagrams = dict()

# diagrams
diagrams['digit'] = Diagram(
    Start(type='complex', label="digit"),
    "\"0\"..\"9\""
)

diagrams['letter'] = Diagram(
    Start(type='complex', label="letter"),
    Choice(0, "\"a\"..\"z\"", "\"A\"..\"Z\"")
)

diagrams['identifier'] = Diagram(
    Start(type='complex', label="identifier"),
    Sequence(
        Choice(
            0,
            NonTerminal('letter'),
            "\"_\""
        ),
        ZeroOrMore(
            Choice(
                1,
                NonTerminal('letter'),
                NonTerminal('digit'),
                "\"_\""
            )
        )
    ),
    End()
)

diagrams['numberLiteral'] = Diagram(
    Start(type='complex', label="numberLiteral"),
    Sequence(
        OneOrMore(
            NonTerminal('digit')
        ),
        Optional(
            Sequence(
                "\".\"",
                OneOrMore(
                    NonTerminal('digit')
                ),
            )
        )
    ),
    End()
)
# literals


diagrams['literal'] = Diagram(
    Start(type='complex', label="literal"),
    Choice(
        1,
        NonTerminal("booleanLiteral"),
        NonTerminal("numberLiteral"),
        NonTerminal("stringLiteral")
    )
)

diagrams['stringLiteral'] = Diagram(
    Start(type='complex', label="stringLiteral"),
    "'\"'",
    ZeroOrMore(
        Choice(
            0,
            Terminal("<not \" ASCII character>"),
            Sequence(
                "\"\\\"",
                Choice(
                    0,
                    "'\"'",
                    "\"n\"",
                )
            )
        )
    ),
    "'\"'",

)

diagrams['booleanLiteral'] = Diagram(
    Start(type='complex', label="booleanLiteral"),
    Choice(
        0,
        Terminal("\"true\""),
        Terminal("\"false\"")
    )
)

# specifiers

diagrams['typeSpecifier'] = Diagram(
    Start(type='complex', label="typeSpecifier"),
    Choice(
        0,
        Terminal("\"number\""),
        Terminal("\"boolean\""),
        Terminal("\"string\""),
    )
)

diagrams['variableAssignment'] = Diagram(
    Start(type='complex', label="variableAssignment"),
    NonTerminal("TypeSpecifier"),
    NonTerminal("identifier"),
    Sequence(
        "\"=\"",
        NonTerminal("expression")
    )
)

diagrams['deletion'] = Diagram(
    Start(type='complex', label="deletion"),
    Group(
        Sequence(
            "\"~\"",
            NonTerminal("identifier")
        ),
        label="delete identifier"
    )
)

diagrams['expression'] = Diagram(
    Start(type='complex', label="expression"),
    NonTerminal("orExpression"),
)

diagrams['orExpression'] = Diagram(
    Start(type='complex', label="orExpression"),
    NonTerminal("andExpression"),
    ZeroOrMore(
        Sequence(
            NonTerminal("orOperator"),
            NonTerminal("andExpression")
        )
    )
)

diagrams['andExpression'] = Diagram(
    Start(type='complex', label="andExpression"),
    NonTerminal("equalExpression"),
    ZeroOrMore(
        Sequence(
            Terminal('"and"'),
            NonTerminal("equalExpression")
        )
    )
)

diagrams['equalExpression'] = Diagram(
    Start(type='complex', label="equalExpression"),
    NonTerminal("relationExpression"),
    ZeroOrMore(
        Sequence(
            NonTerminal("equalOperator"),
            NonTerminal("relationExpression")
        )
    )
)

diagrams['relationExpression'] = Diagram(
    Start(type='complex', label="relationExpression"),
    NonTerminal("additiveExpression"),
    ZeroOrMore(
        Sequence(
            NonTerminal("relationOperator"),
            NonTerminal("additiveExpression")
        )
    )
)

diagrams['additiveExpression'] = Diagram(
    Start(type='complex', label="additiveExpression"),
    NonTerminal("multiplicativeExpression"),
    ZeroOrMore(
        Sequence(
            NonTerminal("additiveOperator"),
            NonTerminal("multiplicativeExpression")
        )
    )
)

diagrams['multiplicativeExpression'] = Diagram(
    Start(type='complex', label="multiplicativeExpression"),
    NonTerminal("baseExpression"),
    ZeroOrMore(
        Sequence(
            NonTerminal("multiplicativeOperator"),
            NonTerminal("baseExpression")
        )
    )
)

diagrams['baseExpression'] = Diagram(
    Start(type='complex', label="baseExpression"),
    Optional(NonTerminal("unaryOperator")),
    Choice(
        0,
        Group(
            Choice(
                1,
                NonTerminal("identifier"),
                NonTerminal("literal"),
                NonTerminal("functionCall"),
            ),
            label="must be/return a proper type"
        ),
        Sequence(
            "\"(\"",
            NonTerminal("expression"),
            "\")\""
        ),
    ),
)

diagrams['functionDefinition'] = Diagram(
    Start(type='simple', label="functionDefinition"),
    Stack(
        Sequence(
            Optional(
                Group(
                    NonTerminal("typeSpecifier"),
                    label="return type - nil by default"
                ),
            ),
            "\"function\"",
            NonTerminal("identifier"),
        ),
        Group(
            Sequence(
                "\"(\"",
                ZeroOrMore(
                    Sequence(
                        Sequence(
                            NonTerminal("typeSpecifier"), NonTerminal("identifier"),
                        ),
                        ZeroOrMore(
                            Sequence(
                                "\",\"",
                                NonTerminal("typeSpecifier"), NonTerminal("identifier"),
                            )
                        ),
                    )
                ),
                "\")\"",
            ),
            label="arguments"
        ),
        Sequence(
            Group(
                Sequence(
                    ZeroOrMore(
                        NonTerminal("statement")
                    ),
                ),
                label="function body"
            ),
            "\"end\"",
        )
    )
)

diagrams['programStatement'] = Diagram(
    Start(type='complex', label="programStatement"),
    NonTerminal("statement")
)

diagrams['functionCall'] = Diagram(
    Start(type='complex', label="functionCall"),
    NonTerminal("identifier"),
    Group(
        Sequence(
            "\"(\"",
            ZeroOrMore(
                Sequence(
                    Sequence(
                        NonTerminal("expression"),
                    ),
                    ZeroOrMore(
                        Sequence(
                            "\",\"",
                            NonTerminal("expression"),
                        )
                    ),
                )
            ),
            "\")\"",
        ),
        label="arguments"
    ),
)

# operators

diagrams['unaryOperator'] = Diagram(
    Start(type='complex', label="unaryOperator"),
    Choice(
        1,
        "\"!\"",
        "\"$\"",
        NonTerminal("additiveOperator"),
    )
)

diagrams['equalOperator'] = Diagram(
    Start(type='complex', label="equalOperator"),
    Choice(
        0,
        "\"==\"",
        "\"!=\""
    )
)

diagrams['andOperator'] = Diagram(
    Start(type='complex', label="andOperator"),
    Choice(
        0,
        "\"and\"",
        "\"&\"",
    )
)


diagrams['orOperator'] = Diagram(
    Start(type='complex', label="orOperator"),
    Choice(
        0,
        "\"or\"",
        "\"|\"",
    )
)

diagrams['relationOperator'] = Diagram(
    Start(type='complex', label="relationOperator"),
    Choice(
        2,
        "\">\"",
        "\"<\"",
        "\">=\"",
        "\"<=\""
    )
)

diagrams['additiveOperator'] = Diagram(
    Start(type='complex', label="additiveOperator"),
    Choice(
        0,
        "\"+\"",
        "\"-\"",
    )
)

diagrams['multiplicativeOperator'] = Diagram(
    Start(type='complex', label="multiplicativeOperator"),
    Choice(
        1,
        "\"/\"",
        "\"*\"",
        "\"%\"",
    )
)

diagrams['statement'] = Diagram(
    Start(type='complex', label="statement"),
    Sequence(
        Choice(
            2,
            NonTerminal("ifStatement"),
            NonTerminal("whileStatement"),
            NonTerminal("functionDefinition"),
            Sequence(
                Choice(
                    4,
                    NonTerminal("deletion"),
                    NonTerminal("lambdaAssignment"),
                    NonTerminal("lambdaDefinition"),
                    NonTerminal("functionCall"),
                    Terminal("\"exit\""),
                    Group(
                        NonTerminal("returnStatement"),
                        label="callable only in function body"
                    ),
                    Group(
                        Choice(
                            1,
                            Terminal("\"break\""),
                            Terminal("\"continue\""),
                        ),
                        label="callable only in while statement"
                    ),
                ),
                Terminal(";")
            )
        ),
    )
)


diagrams['returnStatement'] = Diagram(
    Start(type='complex', label="returnStatement"),
    Terminal("\"return\""),
    Group(
        Optional(
            Choice(
                0,
                NonTerminal("expression"),
            )
        ),
        label="expression type must match function return type"
    ),
    Terminal(";")

)

diagrams['ifStatement'] = Diagram(
    Start(type='complex', label="ifStatement"),
    Stack(
        Sequence(
            "\"if\"",
            "\"(\"",
            NonTerminal("expression"),
            "\")\"",
            ZeroOrMore(NonTerminal("statement")),

        ),
        Sequence(
            ZeroOrMore(
                Sequence(
                    "\"elif\"",
                    "\"(\"",
                    NonTerminal("expression"),
                    "\")\"",
                    ZeroOrMore(NonTerminal("statement")),
                )
            )
        ),
        Sequence(
            Optional(
                Sequence(
                    "\"else\"",
                    ZeroOrMore(NonTerminal("statement")),
                )
            ),
            "\"end\""
        ),
    )
)

diagrams['whileStatement'] = Diagram(
    Start(type='complex', label="whileStatement"),
    "\"while\"",
    "\"(\"",
    NonTerminal("expression"),
    "\")\"",
    ZeroOrMore(NonTerminal("statement")),
    "\"end\""
)

diagram_dir = 'diagrams'

try:
    os.mkdir(diagram_dir)
except FileExistsError:
    pass

for name in diagrams:
    file = open(diagram_dir + '/' + name + '.svg', 'w')
    diagrams[name].writeSvg(write=file.write)
    file.close()
# d.writeSvg(sys.stdout.write)
