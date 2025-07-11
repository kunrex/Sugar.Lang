add_library(Sugar STATIC
        compiler.cpp
        compiler.h

        Services/child.cpp
        Services/child.h
        Services/printable.cpp
        Services/printable.h
        Services/collection.cpp
        Services/collection.h
        Services/dictionary.cpp
        Services/dictionary.h
        Services/string_builder.cpp
        Services/string_builder.h
        Services/singleton_service.h

        Lexing/Tokens/token.cpp
        Lexing/Tokens/token.h
        Lexing/Tokens/Enums/type_kind.h
        Lexing/Tokens/Enums/token_type.cpp
        Lexing/Tokens/Enums/token_type.h
        Lexing/Tokens/Enums/syntax_kind.cpp
        Lexing/Tokens/Enums/syntax_kind.h
        Lexing/Tokens/Enums/keyword_type.h
        Lexing/Tokens/Enums/separator_kind.cpp
        Lexing/Tokens/Enums/separator_kind.h

        Lexing/Tokens/Factories/keyword.cpp
        Lexing/Tokens/Factories/keyword.h
        Lexing/Tokens/Factories/constant.cpp
        Lexing/Tokens/Factories/constant.h
        Lexing/Tokens/Factories/operator.cpp
        Lexing/Tokens/Factories/operator.h
        Lexing/Tokens/Factories/separator.cpp
        Lexing/Tokens/Factories/separator.h

        Lexing/Lexer/lexer.cpp
        Lexing/Lexer/lexer.h

        Parsing/ParseNodes/Enums/node_type.h

        Parsing/ParseNodes/parse_node.cpp
        Parsing/ParseNodes/parse_node.h
        Parsing/ParseNodes/invalid_node.cpp
        Parsing/ParseNodes/invalid_node.h

        Parsing/ParseNodes/Values/null_node.cpp
        Parsing/ParseNodes/Values/null_node.h
        Parsing/ParseNodes/Values/this_node.cpp
        Parsing/ParseNodes/Values/this_node.h
        Parsing/ParseNodes/Values/identifier_node.cpp
        Parsing/ParseNodes/Values/identifier_node.h

        Parsing/ParseNodes/Constants/constant_node.cpp
        Parsing/ParseNodes/Constants/constant_node.h

        Parsing/ParseNodes/Types/Keyword/void_type_node.cpp
        Parsing/ParseNodes/Types/Keyword/void_type_node.h
        Parsing/ParseNodes/Types/Created/created_type_node.cpp
        Parsing/ParseNodes/Types/Created/created_type_node.h
        Parsing/ParseNodes/Types/BuiltIn/built_in_type_node.cpp
        Parsing/ParseNodes/Types/BuiltIn/built_in_type_node.h
        Parsing/ParseNodes/Types/Keyword/anonymous_type_node.cpp
        Parsing/ParseNodes/Types/Keyword/anonymous_type_node.h
        Parsing/ParseNodes/Types/Keyword/Generic/list_type_node.cpp
        Parsing/ParseNodes/Types/Keyword/Generic/list_type_node.h
        Parsing/ParseNodes/Types/Keyword/Generic/func_type_node.cpp
        Parsing/ParseNodes/Types/Keyword/Generic/func_type_node.h
        Parsing/ParseNodes/Types/Keyword/Generic/array_type_node.cpp
        Parsing/ParseNodes/Types/Keyword/Generic/array_type_node.h
        Parsing/ParseNodes/Types/Keyword/Generic/tuple_type_node.cpp
        Parsing/ParseNodes/Types/Keyword/Generic/tuple_type_node.h
        Parsing/ParseNodes/Types/Keyword/Generic/action_type_node.cpp
        Parsing/ParseNodes/Types/Keyword/Generic/action_type_node.h
        Parsing/ParseNodes/Types/Keyword/Generic/nullable_type_node.cpp
        Parsing/ParseNodes/Types/Keyword/Generic/nullable_type_node.h
        Parsing/ParseNodes/Types/Keyword/Generic/dictionary_type_node.cpp
        Parsing/ParseNodes/Types/Keyword/Generic/dictionary_type_node.h

        Parsing/ParseNodes/Expressions/Unary/unary_node.cpp
        Parsing/ParseNodes/Expressions/Unary/unary_node.h
        Parsing/ParseNodes/Expressions/Binary/binary_node.cpp
        Parsing/ParseNodes/Expressions/Binary/binary_node.h
        Parsing/ParseNodes/Expressions/dot_expression_node.cpp
        Parsing/ParseNodes/Expressions/dot_expression_node.h
        Parsing/ParseNodes/Expressions/Ternary/ternary_node.cpp
        Parsing/ParseNodes/Expressions/Ternary/ternary_node.h
        Parsing/ParseNodes/Expressions/cast_expression_node.cpp
        Parsing/ParseNodes/Expressions/cast_expression_node.h

        Parsing/ParseNodes/Statements/empty_node.cpp
        Parsing/ParseNodes/Statements/empty_node.h
        Parsing/ParseNodes/Statements/declaration_node.cpp
        Parsing/ParseNodes/Statements/declaration_node.h
        Parsing/ParseNodes/Statements/Control/break_node.cpp
        Parsing/ParseNodes/Statements/Control/break_node.h
        Parsing/ParseNodes/Statements/Control/return_node.cpp
        Parsing/ParseNodes/Statements/Control/return_node.h
        Parsing/ParseNodes/Statements/initialisation_node.cpp
        Parsing/ParseNodes/Statements/initialisation_node.h
        Parsing/ParseNodes/Statements/throw_statement_node.cpp
        Parsing/ParseNodes/Statements/throw_statement_node.h
        Parsing/ParseNodes/Statements/import_statement_node.cpp
        Parsing/ParseNodes/Statements/import_statement_node.h
        Parsing/ParseNodes/Statements/Control/continue_node.cpp
        Parsing/ParseNodes/Statements/Control/continue_node.h
        Parsing/ParseNodes/Statements/expression_statement_node.cpp
        Parsing/ParseNodes/Statements/expression_statement_node.h

        Parsing/ParseNodes/Describers/describer_node.cpp
        Parsing/ParseNodes/Describers/describer_node.h

        Parsing/ParseNodes/Functions/Calling/function_call_node.cpp
        Parsing/ParseNodes/Functions/Calling/function_call_node.h
        Parsing/ParseNodes/Functions/Calling/constructor_call_node.cpp
        Parsing/ParseNodes/Functions/Calling/constructor_call_node.h
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/input_node.cpp
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/input_node.h
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/print_node.cpp
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/print_node.h
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/invoke_node.cpp
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/invoke_node.h
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/format_node.cpp
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/format_node.h
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/funcref_node.cpp
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/funcref_node.h
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/tostring_node.cpp
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/tostring_node.h

        Parsing/ParseNodes/Functions/Creation/explicit_cast_node.cpp
        Parsing/ParseNodes/Functions/Creation/explicit_cast_node.h
        Parsing/ParseNodes/Functions/Creation/implicit_cast_node.cpp
        Parsing/ParseNodes/Functions/Creation/implicit_cast_node.h
        Parsing/ParseNodes/Functions/Creation/operator_overload_node.cpp
        Parsing/ParseNodes/Functions/Creation/operator_overload_node.h
        Parsing/ParseNodes/Functions/Creation/function_creation_node.cpp
        Parsing/ParseNodes/Functions/Creation/function_creation_node.h
        Parsing/ParseNodes/Functions/Creation/constructor_creation_node.cpp
        Parsing/ParseNodes/Functions/Creation/constructor_creation_node.h

        Parsing/ParseNodes/DataTypes/class_node.cpp
        Parsing/ParseNodes/DataTypes/class_node.h
        Parsing/ParseNodes/DataTypes/struct_node.cpp
        Parsing/ParseNodes/DataTypes/struct_node.h
        Parsing/ParseNodes/DataTypes/enum_node.cpp
        Parsing/ParseNodes/DataTypes/enum_node.h

        Parsing/ParseNodes/Conditions/if_node.cpp
        Parsing/ParseNodes/Conditions/if_node.h
        Parsing/ParseNodes/Conditions/else_node.cpp
        Parsing/ParseNodes/Conditions/else_node.h

        Parsing/ParseNodes/Loops/while_node.cpp
        Parsing/ParseNodes/Loops/while_node.h
        Parsing/ParseNodes/Loops/for_loop_node.cpp
        Parsing/ParseNodes/Loops/for_loop_node.h
        Parsing/ParseNodes/Loops/do_while_node.cpp
        Parsing/ParseNodes/Loops/do_while_node.h

        Parsing/ParseNodes/Properties/base_indexer_node.cpp
        Parsing/ParseNodes/Properties/base_indexer_node.h
        Parsing/ParseNodes/Properties/Accessors/get_node.cpp
        Parsing/ParseNodes/Properties/Accessors/get_node.h
        Parsing/ParseNodes/Properties/Accessors/set_node.cpp
        Parsing/ParseNodes/Properties/Accessors/set_node.h
        Parsing/ParseNodes/Properties/base_property_node.cpp
        Parsing/ParseNodes/Properties/base_property_node.h

        Parsing/Parser/parser.cpp
        Parsing/Parser/parser.h
        Parsing/Parser/parser_general.cpp
        Parsing/Parser/parser_functions.cpp
        Parsing/Parser/parser_data_types.cpp
        Parsing/Parser/parser_expressions.cpp
        Parsing/Parser/parser_loops_conditions.cpp

        Analysis/Structure/source_object.cpp
        Analysis/Structure/source_object.h
        Analysis/Structure/source_directory.cpp
        Analysis/Structure/source_directory.h
        Analysis/Structure/Enums/source_type.h
        Analysis/Structure/source_file.cpp
        Analysis/Structure/source_file.h
        Analysis/Structure/Enums/member_type.h
        Analysis/Structure/Core/Interfaces/i_node.h
        Analysis/Structure/Core/nameable.cpp
        Analysis/Structure/Core/nameable.h
        Analysis/Structure/Core/describable.cpp
        Analysis/Structure/Core/describable.h
        Analysis/Structure/Enums/describer.h
        Analysis/Structure/Enums/describer.cpp
        Analysis/Structure/Core/DataTypes/data_type.cpp
        Analysis/Structure/Core/DataTypes/data_type.h
        Analysis/Structure/DataTypes/class.cpp
        Analysis/Structure/DataTypes/class.h
        Analysis/Structure/DataTypes/value_type.cpp
        Analysis/Structure/DataTypes/value_type.h
        Analysis/Structure/DataTypes/enum.cpp
        Analysis/Structure/DataTypes/enum.h
        Analysis/Structure/Core/Creation/characteristic.cpp
        Analysis/Structure/Core/Creation/characteristic.h
        Analysis/Structure/Core/created.cpp
        Analysis/Structure/Core/created.h
        Analysis/Structure/Core/Creation/function.cpp
        Analysis/Structure/Core/Creation/function.h
        Analysis/Structure/Core/Scoped/scoped.cpp
        Analysis/Structure/Core/Scoped/scoped.h
        Analysis/Structure/Global/Functions/void_function.cpp
        Analysis/Structure/Global/Functions/void_function.h
        Analysis/Structure/Global/Functions/method_function.cpp
        Analysis/Structure/Global/Functions/method_function.h
        Analysis/Structure/Global/Functions/operator_overload.cpp
        Analysis/Structure/Global/Functions/operator_overload.h
        Analysis/Structure/Global/Functions/cast_overload.cpp
        Analysis/Structure/Global/Functions/cast_overload.h
        Analysis/Structure/Global/Functions/constructor.cpp
        Analysis/Structure/Global/Functions/constructor.h
        Analysis/Structure/Global/Variables/global_variable.cpp
        Analysis/Structure/Global/Variables/global_variable.h
        Analysis/Creation/Transpiling/cil_transpiler.cpp
        Analysis/Creation/Transpiling/cil_transpiler.h
        Analysis/Structure/Context/context_node.h
        Analysis/Structure/Context/Casts/cast_class_expression.cpp
        Analysis/Structure/Context/Casts/cast_class_expression.h
        Analysis/Structure/Context/Casts/box_cast_expression.cpp
        Analysis/Structure/Context/Casts/box_cast_expression.h
        Analysis/Structure/Context/Casts/unbox_cast_expression.cpp
        Analysis/Structure/Context/Casts/unbox_cast_expression.h
        Analysis/Structure/Context/Casts/defined_cast_expression.cpp
        Analysis/Structure/Context/Casts/defined_cast_expression.h
        Analysis/Structure/Context/binary_context_node.cpp
        Analysis/Structure/Context/binary_context_node.h
        Analysis/Structure/Context/unary_context_node.cpp
        Analysis/Structure/Context/unary_context_node.h
        Analysis/Structure/Core/Interfaces/i_read_write.h
        Analysis/Structure/Core/Interfaces/i_slot_size.h
        Analysis/Structure/Local/Variables/local_variable.cpp
        Analysis/Structure/Local/Variables/local_variable.h
        Analysis/Structure/Context/Entities/References/local_variable_context.cpp
        Analysis/Structure/Context/Entities/References/local_variable_context.h
        Analysis/Structure/Context/Entities/References/parameter_context.cpp
        Analysis/Structure/Context/Entities/References/parameter_context.h
        Analysis/Structure/Context/Entities/References/field_context.cpp
        Analysis/Structure/Context/Entities/References/field_context.h
        Analysis/Structure/Context/Entities/References/property_context.cpp
        Analysis/Structure/Context/Entities/References/property_context.h
        Analysis/Structure/Context/Entities/Functions/function_call_context.cpp
        Analysis/Structure/Context/Entities/Functions/function_call_context.h
        Analysis/Structure/Context/Expressions/dot_expression.cpp
        Analysis/Structure/Context/Expressions/dot_expression.h
        Analysis/Structure/Context/Expressions/indexer_expression.cpp
        Analysis/Structure/Context/Expressions/indexer_expression.h
        Analysis/Structure/Context/Expressions/defined_unary_expression.cpp
        Analysis/Structure/Context/Expressions/defined_unary_expression.h
        Analysis/Structure/Context/Expressions/defined_binary_expression.cpp
        Analysis/Structure/Context/Expressions/defined_binary_expression.h
        Analysis/Structure/Context/context_node.cpp
        Analysis/Structure/Context/Entities/Functions/print_context.cpp
        Analysis/Structure/Context/Entities/Functions/print_context.h
        Analysis/Structure/Context/Entities/Functions/format_context.cpp
        Analysis/Structure/Context/Entities/Functions/format_context.h
        Analysis/Structure/Context/Entities/Functions/input_context.cpp
        Analysis/Structure/Context/Entities/Functions/input_context.h
        Exceptions/log_exception.cpp
        Exceptions/log_exception.h
        Exceptions/exception_manager.cpp
        Exceptions/exception_manager.h
        Exceptions/Compilation/Lexing/constant_out_of_range_exception.cpp
        Exceptions/Compilation/Lexing/constant_out_of_range_exception.h
        Exceptions/Compilation/source_file_exception.cpp
        Exceptions/Compilation/source_file_exception.h
        Exceptions/Compilation/Lexing/character_expected_exception.cpp
        Exceptions/Compilation/Lexing/character_expected_exception.h
        Exceptions/Compilation/Lexing/invalid_character_exception.cpp
        Exceptions/Compilation/Lexing/invalid_character_exception.h

        Exceptions/Compilation/Parsing/token_expected_exception.cpp
        Exceptions/Compilation/Parsing/token_expected_exception.h

        Exceptions/Compilation/Parsing/parsing_exception.cpp
        Exceptions/Compilation/Parsing/parsing_exception.h
        Exceptions/Compilation/Parsing/generic_argument_exception.cpp
        Exceptions/Compilation/Parsing/generic_argument_exception.h
        Exceptions/Compilation/Parsing/invalid_token_exception.cpp
        Exceptions/Compilation/Parsing/invalid_token_exception.h
        Parsing/ParseNodes/Groups/compound_declaration_node.cpp
        Parsing/ParseNodes/Groups/compound_declaration_node.h
        Parsing/ParseNodes/Groups/scope_node.cpp
        Parsing/ParseNodes/Groups/scope_node.h
        Parsing/ParseNodes/Groups/expression_list_node.cpp
        Parsing/ParseNodes/Groups/expression_list_node.h
        Exceptions/Compilation/Parsing/invalid_expression_exception.cpp
        Exceptions/Compilation/Parsing/invalid_expression_exception.h
        Exceptions/Compilation/Parsing/empty_expression_exception.cpp
        Exceptions/Compilation/Parsing/empty_expression_exception.h
        Exceptions/Compilation/Parsing/function_argument_exception.cpp
        Exceptions/Compilation/Parsing/function_argument_exception.h
        Parsing/ParseNodes/Groups/if_chain_node.cpp
        Parsing/ParseNodes/Groups/if_chain_node.h
        Parsing/ParseNodes/Groups/source_file_node.cpp
        Parsing/ParseNodes/Groups/source_file_node.h
        Analysis/Structure/Wrappers/Reference/string.cpp
        Analysis/Structure/Wrappers/Reference/string.h

        Exceptions/Compilation/transpile_file_exception.cpp
        Exceptions/Compilation/transpile_file_exception.h
        Exceptions/Compilation/Analysis/invalid_describer_exception.cpp
        Exceptions/Compilation/Analysis/invalid_describer_exception.h

        Exceptions/Compilation/Analysis/Project/invalid_import_path_exception.cpp
        Exceptions/Compilation/Analysis/Project/invalid_import_path_exception.h
        Exceptions/Compilation/Analysis/Project/duplicate_structure_definition_exception.cpp
        Exceptions/Compilation/Analysis/Project/duplicate_structure_definition_exception.h
        Analysis/Creation/Binding/global_binder.cpp
        Analysis/Creation/Binding/global_binder.h
        Exceptions/Compilation/Analysis/Project/ambiguous_import_exception.cpp
        Exceptions/Compilation/Analysis/Project/ambiguous_import_exception.h
        Analysis/Creation/Binding/binder_extensions.cpp
        Analysis/Creation/Binding/binder_extensions.h
        Analysis/Structure/Wrappers/Generic/array.cpp
        Analysis/Structure/Wrappers/Generic/array.h
        Analysis/Structure/Wrappers/Generic/list.cpp
        Analysis/Structure/Wrappers/Generic/list.h
        Analysis/Structure/Wrappers/Generic/nullable.cpp
        Analysis/Structure/Wrappers/Generic/nullable.h
        Analysis/Structure/Wrappers/Generic/dictionary.cpp
        Analysis/Structure/Wrappers/Generic/dictionary.h
        Analysis/Structure/Wrappers/Generic/tuple.cpp
        Analysis/Structure/Wrappers/Generic/tuple.h
        Analysis/Structure/Wrappers/Reference/object.cpp
        Analysis/Structure/Wrappers/Reference/object.h
        Analysis/Structure/Wrappers/Value/Integer.cpp
        Analysis/Structure/Wrappers/Value/Integer.h
        Analysis/Structure/Wrappers/Value/Boolean.cpp
        Analysis/Structure/Wrappers/Value/Boolean.h
        Analysis/Structure/Wrappers/Value/Character.cpp
        Analysis/Structure/Wrappers/Value/Character.h
        Analysis/Structure/Wrappers/Value/Short.cpp
        Analysis/Structure/Wrappers/Value/Short.h
        Analysis/Structure/Wrappers/Value/Long.cpp
        Analysis/Structure/Wrappers/Value/Long.h
        Analysis/Structure/Wrappers/Value/Float.cpp
        Analysis/Structure/Wrappers/Value/Float.h
        Analysis/Structure/Wrappers/Value/Double.cpp
        Analysis/Structure/Wrappers/Value/Double.h
        Analysis/Structure/Wrappers/Generic/action.cpp
        Analysis/Structure/Wrappers/Generic/action.h
        Analysis/Structure/Wrappers/Generic/func.cpp
        Analysis/Structure/Wrappers/Generic/func.h
        Analysis/Structure/Wrappers/Generic/generic_extensions.cpp
        Analysis/Structure/Wrappers/Generic/generic_extensions.h
        Analysis/Structure/Local/Variables/function_parameter.cpp
        Analysis/Structure/Local/Variables/function_parameter.h
        Parsing/ParseNodes/Properties/assigned_property_node.cpp
        Parsing/ParseNodes/Properties/assigned_property_node.h
        Analysis/Creation/Binding/local_binder.cpp
        Analysis/Creation/Binding/local_binder.h
        Analysis/Structure/Global/Properties/indexer.cpp
        Analysis/Structure/Global/Properties/indexer.h
        Analysis/Structure/Global/Properties/property.cpp
        Analysis/Structure/Global/Properties/property.h
        Analysis/Structure/Context/invalid_context.cpp
        Analysis/Structure/Context/invalid_context.h
        Analysis/Structure/Context/Casts/invalid_cast_expression.cpp
        Analysis/Structure/Context/Casts/invalid_cast_expression.h
        Analysis/Structure/Context/Expressions/invalid_unary_expression.cpp
        Analysis/Structure/Context/Expressions/invalid_unary_expression.h
        Analysis/Structure/Context/Expressions/invalid_binary_expression.cpp
        Analysis/Structure/Context/Expressions/invalid_binary_expression.h
        Analysis/Structure/Context/Expressions/invalid_indexer_expression.cpp
        Analysis/Structure/Context/Expressions/invalid_indexer_expression.h
        Analysis/Structure/Context/Entities/Functions/invalid_function_context.cpp
        Analysis/Structure/Context/Entities/Functions/invalid_function_context.h
        Analysis/Structure/Context/Control/return.cpp
        Analysis/Structure/Context/Control/return.h
        Analysis/Structure/Context/Control/branch.cpp
        Analysis/Structure/Context/Control/branch.h
        Analysis/Structure/Context/Constants/integer_constant.cpp
        Analysis/Structure/Context/Constants/integer_constant.h
        Analysis/Structure/Context/Constants/string_constant.cpp
        Analysis/Structure/Context/Constants/string_constant.h
        Analysis/Structure/Context/Constants/float_constant.cpp
        Analysis/Structure/Context/Constants/float_constant.h
        Analysis/Structure/Context/Constants/null_constant.cpp
        Analysis/Structure/Context/Constants/null_constant.h
        Analysis/Structure/Wrappers/Reference/exception.cpp
        Analysis/Structure/Wrappers/Reference/exception.h
        Exceptions/Compilation/Analysis/variable_definition_exception.cpp
        Exceptions/Compilation/Analysis/variable_definition_exception.h
        Analysis/Structure/Local/Scopes/scope.cpp
        Analysis/Structure/Local/Scopes/scope.h
        Analysis/Structure/Enums/scope_type.h
        Analysis/Structure/Enums/scope_type.cpp

        Analysis/Creation/Binding/project_binder.cpp
        Analysis/Creation/Binding/project_binder.h
        Exceptions/Compilation/Analysis/static_binding_exception.cpp
        Exceptions/Compilation/Analysis/static_binding_exception.h
        Exceptions/Compilation/Analysis/Global/return_accessibility_exception.cpp
        Exceptions/Compilation/Analysis/Global/return_accessibility_exception.h
        Exceptions/Compilation/Analysis/type_exception.cpp
        Exceptions/Compilation/Analysis/type_exception.h
        Exceptions/Compilation/Analysis/Global/invalid_global_statement_exception.cpp
        Exceptions/Compilation/Analysis/Global/invalid_global_statement_exception.h
        Exceptions/Compilation/Analysis/Global/duplicate_function_definition_exception.cpp
        Exceptions/Compilation/Analysis/Global/duplicate_function_definition_exception.h
        Exceptions/Compilation/Analysis/Global/non_static_member_definition_exception.cpp
        Exceptions/Compilation/Analysis/Global/non_static_member_definition_exception.h
        Analysis/Structure/Wrappers/Generic/referenced.cpp
        Analysis/Structure/Wrappers/Generic/referenced.h
        Analysis/Structure/Wrappers/Reference/math.cpp
        Analysis/Structure/Wrappers/Reference/math.h
        Exceptions/compile_exception.cpp
        Exceptions/compile_exception.h
        Exceptions/Compilation/Analysis/Local/read_write_exception.cpp
        Exceptions/Compilation/Analysis/Local/read_write_exception.h
        Analysis/Structure/Core/Creation/variable.cpp
        Analysis/Structure/Core/Creation/variable.h
        Analysis/Structure/Core/Interfaces/i_created.h
        Analysis/Structure/Core/Interfaces/i_describable.h
        Analysis/Structure/DataTypes/data_type_extensions.cpp
        Analysis/Structure/DataTypes/data_type_extensions.h
        Analysis/Structure/Core/Interfaces/i_fully_nameable.h
        Parsing/ParseNodes/Functions/Calling/collection_construction_call_node.cpp
        Parsing/ParseNodes/Functions/Calling/collection_construction_call_node.h
        Analysis/Structure/Core/Interfaces/DataTypes/i_data_type.h
        Analysis/Structure/Core/Interfaces/i_nameable.h
        Analysis/Structure/Core/Interfaces/Creation/i_function.h
        Analysis/Structure/Core/Interfaces/Creation/i_parametrized.h
        Analysis/Structure/Core/Interfaces/Creation/i_built_in_function.h
        Analysis/Structure/Core/Interfaces/Creation/i_variable.h
        Analysis/Structure/Core/Interfaces/Creation/i_function_definition.h
        Analysis/Structure/Core/Interfaces/Creation/i_property_signature.h
        Analysis/Structure/Core/Interfaces/Creation/i_indexer_definition.h
        Analysis/Structure/Core/Interfaces/Creation/i_characteristic.h
        Analysis/Structure/Core/Interfaces/Creation/i_operator_overload.h
        Analysis/Structure/Core/built_in_function.cpp
        Analysis/Structure/Core/built_in_function.h
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/ref_call_node.cpp
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/ref_call_node.h
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/copy_coll_node.cpp
        Parsing/ParseNodes/Functions/Calling/BaseFunctions/copy_coll_node.h
        Analysis/Structure/Core/Interfaces/Context/i_context_node.h
        Analysis/Structure/Context/Entities/static_reference_context.cpp
        Analysis/Structure/Context/Entities/static_reference_context.h
        Analysis/Structure/Context/Entities/this_context.cpp
        Analysis/Structure/Context/Entities/this_context.h
        Analysis/Structure/Context/Entities/Functions/funcref_context.cpp
        Analysis/Structure/Context/Entities/Functions/funcref_context.h
        Analysis/Structure/Context/Entities/Functions/invoke_context.cpp
        Analysis/Structure/Context/Entities/Functions/invoke_context.h
        Analysis/Structure/Context/Entities/Functions/function_extensions.cpp
        Analysis/Structure/Context/Entities/Functions/function_extensions.h
        Analysis/Structure/Context/Expressions/assignment_expression.cpp
        Analysis/Structure/Context/Expressions/assignment_expression.h
        Analysis/Structure/Context/Expressions/duplicate_expression.cpp
        Analysis/Structure/Context/Expressions/duplicate_expression.h
        Exceptions/Compilation/Analysis/Local/non_static_reference_exception.cpp
        Exceptions/Compilation/Analysis/Local/non_static_reference_exception.h
        Exceptions/Compilation/Analysis/Local/accessibility_exception.cpp
        Exceptions/Compilation/Analysis/Local/accessibility_exception.h
        Analysis/Structure/Context/Entities/Functions/invalid_funcref_context.cpp
        Analysis/Structure/Context/Entities/Functions/invalid_funcref_context.h
        Analysis/Structure/Context/Entities/Functions/copy_context.cpp
        Analysis/Structure/Context/Entities/Functions/copy_context.h
        Analysis/Structure/Context/Entities/Functions/ref_context.cpp
        Analysis/Structure/Context/Entities/Functions/ref_context.h
        Analysis/Structure/Context/Entities/Functions/creation_context.cpp
        Analysis/Structure/Context/Entities/Functions/creation_context.h
        Analysis/Structure/Core/Interfaces/DataTypes/i_user_defined_type.h
        Analysis/Structure/Core/Interfaces/scoped/i_scoped.h
        Analysis/Structure/Wrappers/Reference/void.cpp
        Analysis/Structure/Wrappers/Reference/void.h
        Analysis/Structure/Compilation/compilation_result.cpp
        Analysis/Structure/Compilation/compilation_result.h
        Lexing/Tokens/Enums/operator_kind.h
        Lexing/Tokens/Enums/operator_kind.cpp
        Analysis/Structure/Global/Variables/global_constant.cpp
        Analysis/Structure/Global/Variables/global_constant.h
        Exceptions/Compilation/Analysis/Local/invalid_statement_exception.cpp
        Exceptions/Compilation/Analysis/Local/invalid_statement_exception.h
        Exceptions/Compilation/Analysis/Local/overload_not_found_exception.cpp
        Exceptions/Compilation/Analysis/Local/overload_not_found_exception.h
        Analysis/Structure/Core/Interfaces/DataTypes/i_delegate_type.h
        Analysis/Structure/Context/Control/throw.cpp
        Analysis/Structure/Context/Control/throw.h
        Analysis/Structure/Context/Expressions/ternary_expression.cpp
        Analysis/Structure/Context/Expressions/ternary_expression.h
        Analysis/Structure/Context/Expressions/invalid_ternary_expression.cpp
        Analysis/Structure/Context/Expressions/invalid_ternary_expression.h
        Analysis/Structure/Core/Interfaces/DataTypes/i_collection_type.h
        Parsing/ParseNodes/Core/Interfaces/i_parse_node.h
        Parsing/ParseNodes/Enums/child_code.h
        Parsing/ParseNodes/Expressions/indexer_expression_node.cpp
        Parsing/ParseNodes/Describers/describer_keyword_node.cpp
        Parsing/ParseNodes/Describers/describer_keyword_node.h
        Analysis/Structure/Core/Interfaces/DataTypes/i_primitive_type.h
        Analysis/Structure/Core/Interfaces/Creation/i_built_in_overload.h
        Analysis/Structure/Core/Interfaces/Creation/i_built_in_cast.h
        Analysis/Structure/Wrappers/Value/built_in_functions.cpp
        Analysis/Structure/Wrappers/Value/built_in_functions.h
        Analysis/Structure/Core/Interfaces/i_bindable.h
        Analysis/Structure/Core/Interfaces/Creation/i_built_in_parametrized.h
        Analysis/Structure/Core/Interfaces/i_transpilable.h
        Exceptions/Compilation/Analysis/Local/return_value_exception.cpp
        Exceptions/Compilation/Analysis/Local/return_value_exception.h
        Analysis/Structure/Core/Interfaces/Creation/i_constructor.h
        Exceptions/Compilation/Analysis/Local/accessor_body_exception.cpp
        Exceptions/Compilation/Analysis/Local/accessor_body_exception.h
        Analysis/Creation/Binding/constant_binder.cpp
        Analysis/Creation/Binding/constant_binder.h
        Exceptions/Compilation/Analysis/Local/initialisation_exception.cpp
        Exceptions/Compilation/Analysis/Local/initialisation_exception.h
        Exceptions/Compilation/Analysis/Local/constant_expected_exception.cpp
        Exceptions/Compilation/Analysis/Local/constant_expected_exception.h
        Analysis/Structure/Context/Expressions/pop_expression.cpp
        Analysis/Structure/Context/Expressions/pop_expression.h
        Lexing/Tokens/Enums/type_kind.cpp
        Analysis/Structure/Global/Functions/function_definition.cpp
        Analysis/Structure/Global/Functions/function_definition.h
        Exceptions/Compilation/Analysis/binding_exception.cpp
        Exceptions/Compilation/Analysis/binding_exception.h
)